/**
 *************************************************************************
 *
 * @file world_map.cpp
 *
 * Management of the world map, implementation.
 *
 ************************************************************************/


#include "world_map.hpp"


#include <time.h> 
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>


#include "exception.hpp"
#include "creature.hpp"


namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// world_map
//
//////////////////////////////////////////////////////////////////////////


world_map::world_map(int size_x, int size_y)
	: size_x_(size_x), size_y_(size_y)
{
	if (size_x <= 0 || size_y <= 0 ||
		size_x > max_size_x_ || size_y > max_size_y_)
	{
		std::cerr << "Provided invalid world dimensions." << std::endl;
		throw invalid_parameter();
	}

	tiles_.reserve(size_x * size_y);

	std::vector<float> noise(perlin_noise(size_x, size_y));

	for (int y = 0; y < size_y; ++y)
	for (int x = 0; x < size_x; ++x)
		tiles_.push_back(world_tile(noise_to_climate(noise[y * size_x + x])));
}


world_tile& world_map::at(int x, int y)
{
	if (x < 0 || y < 0 || x >= size_x_ || y >= size_y_)
	{
		std::cerr << "Requested invalid world tile." << std::endl;
		throw invalid_parameter();
	}

	return tiles_[y * size_x_ + x];
}


const world_tile& world_map::at(int x, int y) const
{
	if (x < 0 || y < 0 || x >= size_x_ || y >= size_y_)
	{
		std::cerr << "Requested invalid world tile." << std::endl;
		throw invalid_parameter();
	}

	return tiles_[y * size_x_ + x];
}


void world_map::move_creature
	(const std::shared_ptr<creature>& c, int x, int y)
{
	if (!c)
	{
		std::cerr << "Can't move NULL creature" << std::endl;
		throw invalid_parameter();
	}

	if (x == c->x() && y == c->y()) return;

	add_creature_to_tile(c);
	remove_creature_from_tile(c);		

	c->x_ = x;
	c->y_ = y;
}


void world_map::add_creature_to_tile(const std::shared_ptr<creature>& c)
{
	if (c->x() < 0 || c->y() < 0 ||
		c->x() >= size_x_ || c->y() >= size_y_)
	{
		std::cerr << "Creature currently is not on a valid map tile." << std::endl;
		return;
	}

	std::vector<std::shared_ptr<creature>>& tile_creatures =
		tiles_[c->y() * size_x_ + c->x()].creatures_;

	tile_creatures.push_back(c);
}


void world_map::remove_creature_from_tile(const std::shared_ptr<creature>& c) NOTHROW
{
	if (c->x() < 0 || c->y() < 0 ||
		c->x() >= size_x_ || c->y() >= size_y_)
	{
		std::cerr << "Creature currently is not on a valid map tile." << std::endl;
		return;
	}

	std::vector<std::shared_ptr<creature>>& tile_creatures =
		tiles_[c->y() * size_x_ + c->x()].creatures_;

	while (true)
	{
		std::vector<std::shared_ptr<creature>>::iterator creatureit =
			find(tile_creatures.begin(), tile_creatures.end(), c);

		if (creatureit == tile_creatures.end()) break;

		tile_creatures.erase(creatureit);
	}
}


std::vector<float> world_map::perlin_noise
	(int size_x, int size_y)
{
	srand((unsigned int)time(NULL));

	std::vector<float> result;
	result.resize(size_x * size_y);

	for (int i = 0; i < size_x * size_y; ++i)
		result[i] = 0.5f;

	const int max_octave = 32;

	for (int octave = max_octave; octave > 0; octave /= 2)
	{
		int r_size_x = size_x / octave + 2;
		int r_size_y = size_y / octave + 2;

		std::vector<float> randoms;
		randoms.resize(r_size_x * r_size_y);

		for (int ry = 0; ry < r_size_y; ++ry)
		for (int rx = 0; rx < r_size_x; ++rx) 
			randoms[ry * r_size_x + rx] =
				(static_cast<float>(rand()) * 2 / RAND_MAX - 1) *
				 sqrtf(static_cast<float>(octave) / max_octave);

		for (int ry = 0; ry < r_size_y - 1; ++ry)
		for (int rx = 0; rx < r_size_x - 1; ++rx) 
		{
			float values[4] =
				{ randoms[ry * r_size_x + rx],
				  randoms[ry * r_size_x + rx + 1],
				  randoms[(ry + 1) * r_size_x + rx],
				  randoms[(ry + 1) * r_size_x + rx + 1] };

			for (int y = 0; y < octave; ++y)
			for (int x = 0; x < octave; ++x) 
			{
				int tx = x + rx * octave;
				int ty = y + ry * octave;

				if (tx < 0 || tx >= size_x || ty < 0 || ty >= size_y)
					continue;

				float fx = static_cast<float>(x) / octave;
				float fy = static_cast<float>(y) / octave;

				result[ty * size_x + tx] +=
					(1 - fx) * (1 - fy) * values[0] +
					fx * (1 - fy) * values[1] +
					(1 - fx) * fy * values[2] +
					fx * fy * values[3];
			}
		}
	}

	float maximum = 0;
	for (int i = 0; i < size_x * size_y; ++i)
		maximum = std::max(maximum, fabsf(result[i]));

	for (int i = 0; i < size_x * size_y; ++i)
		result[i] = fabsf(result[i]) / maximum;

	return result;
}


world_tile::climate_type world_map::noise_to_climate
	(float noise)
{
	float intervals[world_tile::climate_count - 1] =
		{ 0.16f, 0.32f, 0.48f, 0.64f, 0.80f };

	world_tile::climate_type indexed[world_tile::climate_count - 1] =
		{ world_tile::deep_water, world_tile::shallow_water,
		  world_tile::sand, world_tile::earth, world_tile::stones };

	for (int i = 0; i < world_tile::climate_count - 1; ++i)
		if (noise < intervals[i]) return indexed[i];

	return world_tile::snow;
}




} /* namespace biosim */