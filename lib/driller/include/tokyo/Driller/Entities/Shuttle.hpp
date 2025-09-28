#pragma once

#include <tokyo/Game/Resource/Resource.hpp>
#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Driller/Entities/Worker.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace drl
{

	using ShuttlePrototypeId = IdType;
	using ShuttleId = IdType;

	enum class ShuttleState
	{
		Idle,
		TravellingToSurface,
		WaitingOnSurface,
		LeavingSurface,
		Completed
	};

	struct ShuttleInstance
	{
		ShuttleId Id;
		ShuttlePrototypeId prototypeId;
		ShuttleState state;
		float elapsed;
		sf::Vector2f position;
		sf::Vector2f startingPosition;
		sf::Vector2f surfacePosition;
		sf::Vector2f leavingPosition;
		std::unordered_map<WorkerPrototypeId, int> passengers;
		std::unordered_map<tokyo::ResourceId, tokyo::ResourceValue> cargo;
	};
	struct ShuttlePrototype
	{
		std::string name;
		sf::Vector2i size;
		sf::Vector2i texture; // Top Left corner
		float idleTime{ 0.0f };
		float loadingTime{ 0.0f };
		float speed{ 0.0f };
		std::unordered_set<std::string> allowedCargo;
	};

}