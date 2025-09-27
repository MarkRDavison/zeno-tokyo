#pragma once

#include <tokyo/Driller/Constants.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <vector>
#include <string>

namespace drl
{
	using BuildingPrototypeId = IdType;
	using BuildingId = IdType;

	struct BuildingInstance
	{
		BuildingId Id;
		sf::Vector2i coordinates; // Top Left corner
		BuildingPrototypeId prototypeId;
	};

	struct BuildingPrototype
	{
		std::string name;
		sf::Vector2i size;
		sf::Vector2i texture; // Top Left corner
		std::unordered_map<std::string, int> requiredWorkers;
		std::vector<std::pair<std::string, sf::Vector2f>> providedJobs;
	};
}