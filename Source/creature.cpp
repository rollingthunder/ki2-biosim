/**
 *************************************************************************
 *
 * @file creature.cpp
 *
 * Creatures, creature prototypes, and creature management.
 *
 ************************************************************************/


#include "creature.hpp"


#include <iostream>
#include <fstream>
#include <stdlib.h> 


#include "exception.hpp"


namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// creature_prototype
//
//////////////////////////////////////////////////////////////////////////


std::list<creature_prototype>
	creature_prototype::load(const std::string& path)
{
	std::list<creature_prototype> result;

	std::ifstream inputtext;
	inputtext.open(path);

	if (!inputtext)
	{
		std::cerr << "Creature list: " << path << " was not found." << std::endl;
		throw file_operation_failed();
	}
 
	while (!inputtext.eof() && !!inputtext)
	{
		std::string line;
		std::getline(inputtext, line);

		std::vector<std::string> split_line;
		while (true)
		{
			size_t nextstop = line.find_first_of(',');
			split_line.push_back(line.substr(0, nextstop));

			if (nextstop == std::string::npos) break;

			line = line.substr(nextstop + 1);
		}
		
		if (split_line.size() != 6)
		{
			std::cerr << "Line in creature list has too few or too many entries." << std::endl;
			continue;
		}

		try
		{
			std::string name(split_line[0]);
			int strength = atoi(split_line[1].c_str());
			int speed = atoi(split_line[2].c_str());
			int lifetime = atoi(split_line[3].c_str());
			std::string properties(split_line[4]);
			creature_prototype::habitat_type habitat = string_to_habitat(split_line[4]);
			creature_prototype::sustentation_type sustentation = string_to_sustentation(split_line[4]);
			std::unique_ptr<image> graphics(image::load(split_line[5]));
		
			result.push_back
				(creature_prototype(name, strength, speed, lifetime,
									properties, habitat, sustentation, *graphics));
		}
		catch (const std::exception&)
		{
			std::cerr << "Line in creature list contains corrupt data." << std::endl;
			continue;
		}
	}

	return result;
}


creature_prototype::habitat_type
	creature_prototype::string_to_habitat(const std::string& s)
{
	if (s.find("Wasserbewohner") != std::string::npos)
		return creature_prototype::habitat_water;
	else if (s.find("Landbewohner") != std::string::npos)
		return creature_prototype::habitat_land;
	else
	{
		std::cerr << "Creature habitat was not specified." << std::endl;
		throw corrupt_data();
	}
}


creature_prototype::sustentation_type
	creature_prototype::string_to_sustentation(const std::string& s)
{
	if (s.find("Pflanzenfresser") != std::string::npos)
		return creature_prototype::herbivore;
	else if (s.find("Pflanze") != std::string::npos)
		return creature_prototype::plant;
	else if (s.find("Fleischfresser") != std::string::npos)
		return creature_prototype::carnivore;
	else
	{
		std::cerr << "Creature habitat was not specified." << std::endl;
		throw corrupt_data();
	}
}




} /* namespace biosim */
