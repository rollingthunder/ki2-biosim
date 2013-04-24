/**
 *************************************************************************
 *
 * @file world_map.hpp
 *
 * Management of the world map.
 *
 ************************************************************************/


#if !defined(INCLUDED_WORLD_MAP_HPP)
#define INCLUDED_WORLD_MAP_HPP


#include "build_config.hpp"


#include <vector>
#include <memory>


namespace biosim
{


class creature;
class world_map;


/**
 *************************************************************************
 *
 * @class world_tile
 *
 * A single tile within the world, including its climate type, and any
 * creatures within.
 *
 ************************************************************************/
class world_tile
{
	friend class world_map;

	public:

		enum climate_type
			{ deep_water, shallow_water, sand, earth, stones, snow, climate_count };

		typedef std::vector<std::shared_ptr<creature>>::const_iterator creature_iterator;
		creature_iterator begin() const NOTHROW { return creatures_.begin(); }
		creature_iterator end() const NOTHROW { return creatures_.end(); }

		climate_type climate() const NOTHROW { return climate_; }


	private:

		world_tile(climate_type climate)
			: climate_(climate) { }

		std::vector<std::shared_ptr<creature>> creatures_;

		climate_type climate_;
};




/**
 *************************************************************************
 *
 * @class world_map
 *
 * Manages the entire game world, including tiles and creatures.
 *
 ************************************************************************/
class world_map
{
	public:

		world_map(int size_x, int size_y);

		int size_x() const NOTHROW { return size_x_; }
		int size_y() const NOTHROW { return size_y_; }

		world_tile& at(int x, int y);
		const world_tile& at(int x, int y) const;

		void move_creature
			(const std::shared_ptr<creature>& c, int x, int y);

		void add_creature_to_tile(const std::shared_ptr<creature>& c);
		void remove_creature_from_tile(const std::shared_ptr<creature>& c) NOTHROW;


	private:

		static std::vector<float> perlin_noise
			(int size_x, int size_y);
		static world_tile::climate_type noise_to_climate
			(float noise);


		int size_x_;
		int size_y_;

		std::vector<world_tile> tiles_;

		static const int max_size_x_ = 512;
		static const int max_size_y_ = 512;
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_WORLD_MAP_HPP) */
