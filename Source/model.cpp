/**
*************************************************************************
*
* @file model.cpp
*
* Contains the high-level application data model, implementation.
*
************************************************************************/


#include "model.hpp"


#include <iostream>
#include <algorithm>


#include "exception.hpp"


namespace biosim
{

	creature_prototype::habitat_type climate_to_habitat(const world_tile::climate_type& climate)
	{
		if(climate <= world_tile::climate_type::shallow_water)
			return creature_prototype::habitat_type::habitat_water;
		else
			return creature_prototype::habitat_type::habitat_land;
	}


	//////////////////////////////////////////////////////////////////////////
	//
	// model
	//
	//////////////////////////////////////////////////////////////////////////


	model::model()
		:
		prototypes_(creature_prototype::load(default_prototype_list_)),
		map_(default_world_size_x_, default_world_size_y_),
		cursor_x_(0),
		cursor_y_(0)
	{ 
		const int view_distance = 5; 

		behaviors_[creature_prototype::herbivore] = 
			std::make_shared<decision<creature>>(
			[](const creature& c) { return !c.is_alive(); }, // Dead?
			std::make_shared<switchstate_action<creature, creature_state>>(creature_state::do_nothing), // Dead -> Do nothing!
			std::make_shared<decision<creature>>([&](const creature& c){ //Predator near?
				auto near_creatures = locator(view_distance, c.x(), c.y());
				return std::find(near_creatures.cbegin(), near_creatures.cend(), [](const creature& nc) { return nc.prototype.sustentation == creature_prototype::carnivore; }) != near_creatures.cend();
		},
			std::make_shared<switchstate_action<creature, creature_state>>(creature_state::run_away),
			std::make_shared<decision<creature>>([&](const creature& c){ // Food near?
				auto near_creatures = locator(view_distance, c.x(), c.y());
				return std::find(near_creatures.cbegin(), near_creatures.cend(), [](const creature& nc) { return nc.prototype.sustentation == creature_prototype::plant; }) != near_creatures.cend();
		},std::make_shared<switchstate_action<creature, creature_state>>(creature_state::eat),
			std::make_shared<switchstate_action<creature, creature_state>>(creature_state::explore))));
	}


	void model::set_cursor(int x, int y)
	{
		if (x < 0 || x >= map_.size_x() ||
			y < 0 || y >= map_.size_y()) return;

		cursor_x_ = x;
		cursor_y_ = y;
	}


	void model::create_creature_at_cursor
		(const creature_prototype& prototype)
	{
		create_creature(prototype, cursor_x_, cursor_y_);
	}

	std::list<std::shared_ptr<const creature>> model::locator(const int distance,const int x,const int y) const
	{
		std::list<std::shared_ptr<const creature>> near_creatures_;
		std::copy_if(creatures_.cbegin(), creatures_.cend(), near_creatures_, [=](const std::shared_ptr<creature>& c){
			return sqrt((c->x() - x) ^ 2 + (c->y() - y) ^ 2) <= distance;
		});

		return near_creatures_;
	}


	void model::perform_step()
	{
		std::vector<std::weak_ptr<creature>> removeable_creatures;

		for(auto& c : creatures_)
		{
			auto behavior = behaviors_[c->prototype.sustentation];
			if(behavior)
			{
				
			}

			// hostile environment ? 
			if(c->is_alive() && 
				c->prototype.habitat() != climate_to_habitat(map_.at(c->x(), c->y()).climate()))
			{
				c->lifetime = std::max(0, c->lifetime - 50);
			}
			else
			{
				c->lifetime -= 1;
			}

			if(c->lifetime < -2)
				removeable_creatures.push_back(c);
		}

		for(auto& c : removeable_creatures)
			destroy_creature(c);
	}


	std::weak_ptr<creature> model::create_creature
		(const creature_prototype& prototype, int x, int y)
	{
		std::shared_ptr<creature> c(new creature(prototype, x, y));

		if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y())
		{
			std::cerr << "Invalid creature position." << std::endl;
			throw invalid_parameter();
		}

		creatures_.push_back(c);

		try
		{ map_.add_creature_to_tile(c); }
		catch (...)
		{
			creatures_.pop_back();
			throw;
		}

		return c;
	}


	void model::destroy_creature(const std::weak_ptr<creature>& c) NOTHROW
	{
		std::shared_ptr<creature> csp(c.lock());

		if (!csp)
		{
			std::cerr << "Invalid creature for destruction." << std::endl;
			throw invalid_parameter();
		}

		std::list<std::shared_ptr<creature>>::iterator removeit
			(std::find(creatures_.begin(), creatures_.end(), csp));

		if (removeit != creatures_.end())
			creatures_.erase(removeit);		
		else
			std::cerr << "Creature not found in global creature list." << std::endl;

		map_.remove_creature_from_tile(csp);
	}


	void model::move_creature
		(const std::weak_ptr<creature>& c, int x, int y)
	{
		std::shared_ptr<creature> csp(c.lock());

		if (!csp)
		{
			std::cerr << "Invalid creature for movement." << std::endl;
			throw invalid_parameter();
		}

		map_.move_creature(csp, x, y);
	}


	const char *model::default_prototype_list_ = "CreatureTable.txt";

	const int model::default_world_size_x_ = 100;
	const int model::default_world_size_y_ = 100;




} /* namespace biosim */