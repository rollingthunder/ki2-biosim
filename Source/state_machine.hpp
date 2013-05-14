#pragma once

#if !defined(INCLUDED_STATE_MACHINE_HPP)
#define INCLUDED_STATE_MACHINE_HPP
#include "decision_tree.hpp"


namespace biosim
{
	template<typename T, typename TState>
	class switchstate_action : public action<T>
	{
	public:
		switchstate_action(TState resulting_state) : resulting_state_(resulting_state) {} 
		TState resulting_state() const {return resulting_state_;}
	private:
		const TState resulting_state_;
	};

	template<typename T, typename TState>
	class state_machine
	{
	public:
		state_machine(const std::map<TState, std::shared_ptr<decision<T>>>& transitions, const TState initial_state) : current_state_(initial_state), transitions_(transitions) {}

		void step(const T& model) {
			const action<T>& action = transitions_[current_state_]->decide_action(model);
			auto stateswitch = dynamic_cast<switchstate_action<T, TState>*>(&action);

			if(stateswitch)
			{
				current_state_ = stateswitch->resulting_state();
			}
		}
		const TState current_state() const { return current_state_;} 
	private:
		TState current_state_;
		const std::map<TState, std::shared_ptr<decision<T>>> transitions_;

	};

	class herbivore_behavior{

	};
}

#endif