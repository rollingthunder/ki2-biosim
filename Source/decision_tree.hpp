#pragma once

#if !defined(INCLUDED_DECISION_TREE_HPP)
#define INCLUDED_DECISION_TREE_HPP
#include <functional>
#include <memory>
#include <vector>


namespace biosim
{
	template<typename T>
	class decision_tree;

	template<typename T>
	class action;


	template<typename T>
	class node {
	public:
		node(){}
		virtual ~node() {}

		virtual const action<T>& decide_action(T& item) const = 0;		
	};

	template<typename T>
	class action : public node<T> 
	{
		static const std::shared_ptr<const action<T>> no_action;
	};

	

	template<typename T>
	class lambda_action : public action<T>
	{
	public:
		

		const std::function< void(T&) > act;

		action(const std::function<void(T&)>& action) : act(action) {}

		const action<T>& decide_action(T& item) const{
			return *this;
		}
	};

	
	template<typename T>
	const std::shared_ptr<const action<T>> action<T>::no_action = std::make_shared<action<T>>([](T& t){});


	

	template<typename T>
	class decision;

	template<typename T>
	class dynamic_decision : public decision<T>
	{
	public:
		dynamic_decision(const std::function<const std::shared_ptr<node<T>>(const T&)>& decision_lambda) : decision_lambda_(decision_lambda){}

		const action<T>& decide_action(T& item) const {
			return decision_lambda_(item)->decide_action(item);
		}
	private:
		const std::function<const std::shared_ptr<node<T>>(const T&)> decision_lambda_;
	};
	
	template<typename T>
	class binary_decision : public decision<T>
	{	

	public:
		const std::function<bool(const T&)> test;

		const std::shared_ptr<const node<T>> true_branch, false_branch;

		const action<T>& decide_action(T& item) const {
			if(test(item))
				return true_branch->decide_action(item);
			else
				return false_branch->decide_action(item);
		}

		decision(const std::function<bool(const T&)>& test, 
			std::shared_ptr<const node<T>> true_branch = action<T>::no_action,
			std::shared_ptr<const node<T>> false_branch = action<T>::no_action
			) : test(test), true_branch(true_branch), false_branch(false_branch) {}
	};


	template<typename T, typename Scalar = float>
	class inrange : public decision<T>
	{
	public:
		inrange(
			const std::function<Scalar(const T&)> measure_func, 
			Scalar min_inclusive, Scalar max_inclusive,
			std::shared_ptr<const node<T>> true_branch = action<T>::no_action,
			std::shared_ptr<const node<T>> false_branch = action<T>::no_action) : 
			decision<T>([=](const T& item){
				Scalar m = measure_func(item);
				return m >= min_inclusive && 
					m <= max_inclusive;
			}, true_branch, false_branch) {}
	};

	template<typename T, typename ItemType = T>
	class invector : decision<T> 
	{
	public:
			invector(
				std::shared_ptr<std::vector<ItemType>> class_vec, 
				const std::function<const ItemType&(const T&)> select_func = [](const T& i){return i;},
				std::shared_ptr<const node<T>> true_branch = action<T>::no_action,
				std::shared_ptr<const node<T>> false_branch = action<T>::no_action) : 
			decision([=](const T& item){
				const ItemType& m = select_func(item);
				return std::find(class_vec->begin(), class_vec->end(), m) != class_vec->npos;
			}, true_branch, false_branch) {}
	};




	
	
}

#endif