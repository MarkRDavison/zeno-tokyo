#pragma once

#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Driller/Entities/Worker.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
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
	};
	struct ShuttlePrototype
	{
		std::string name;
		sf::Vector2i size;
		sf::Vector2i texture; // Top Left corner
		float idleTime;
		float loadingTime;
		float speed;
	};

}