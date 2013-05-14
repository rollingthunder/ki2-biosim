/**
 *************************************************************************
 *
 * @file creature.hpp
 *
 * Creatures, creature prototypes, and creature management.
 *
 ************************************************************************/


#if !defined(INCLUDED_CREATURE_HPP)
#define INCLUDED_CREATURE_HPP


#include "build_config.hpp"


#include <memory>
#include <string>
#include <list>


#include "image.hpp"


namespace biosim
{


/**
 *************************************************************************
 *
 * @class creature_prototype
 *
 * Defines a type of creature and associated attributes.
 *
 * Usage notes:
 * - Read-only access.
 * - Accessed via a creature_prototype::load_list().
 *
 ************************************************************************/
class creature_prototype
{
	public:

		enum habitat_type { habitat_water, habitat_land };
		enum sustentation_type { plant, herbivore, carnivore };


		const std::string& name() const NOTHROW { return name_; }

		int strength() const NOTHROW { return strength_; }
		int speed() const NOTHROW { return speed_; }
		int lifetime() const NOTHROW { return lifetime_; }

		const std::string& properties() const NOTHROW { return properties_; }
		habitat_type habitat() const NOTHROW { return habitat_; }
		sustentation_type sustentation() const NOTHROW { return sustentation_; }

		const image& graphics() const NOTHROW { return graphics_; }


		/** Load creature prototypes from text file at given path. */
		static std::list<creature_prototype> load(const std::string& path);


	private:

		creature_prototype
			(const std::string& name, int strength, int speed, int lifetime,
			 const std::string& properties, habitat_type habitat, sustentation_type sustentation,
			 const image& graphics)
			:
			name_(name), strength_(strength), speed_(speed), lifetime_(lifetime),
			properties_(properties), habitat_(habitat), sustentation_(sustentation),
			graphics_(graphics)
		{ }

	
		static habitat_type string_to_habitat(const std::string& s);
		static sustentation_type string_to_sustentation(const std::string& s);


		std::string name_;

		int strength_;
		int speed_;
		int lifetime_;

		std::string properties_;
		habitat_type habitat_;
		sustentation_type sustentation_;

		image graphics_;
};




/**
 *************************************************************************
 *
 * @class creature
 *
 * An instance of a creature_prototype.
 *
 * Notes:
 * - Creature lifetime is managed via shared_ptr and weak_ptr.
 *		But a single, owning shared pointer persists for each creature.
 *		Other shared pointers are only locked from weak pointers during
 *		creature access.
 * - Creatures must be created, moved, and destroyed by respective
 *		functions within the model class. This ensures that management
 *		data structures are maintained.
 * - Other creature attributes (lifetime, ...) may be modified freely
 *		by application logics.
 *
 ************************************************************************/
class creature
{
	friend class world_map;

	public:

		creature(const creature_prototype& prototype, int x, int y)
			:
			prototype(prototype), lifetime(prototype.lifetime()),
			x_(x), y_(y)
		{ }


		int x() const NOTHROW { return x_; }
		int y() const NOTHROW { return y_; }

		bool is_alive() const NOTHROW { return lifetime > 0; }

		const creature_prototype& prototype;

		int lifetime;


	private:

		creature(const creature& other); // Non-copyable
		creature& operator =(const creature& other); // Non-assignable

		int x_;
		int y_;

		
};


enum creature_state{
	do_nothing,
	eat,
	run_away,
	explore
};

} /* namespace biosim */


#endif /* !defined(INCLUDED_CREATURE_HPP) */