#pragma once

#include <tokyo/Driller/Constants.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_set>
#include <string>

namespace drl
{
	using WorkerPrototypeId = IdType;
	using WorkerId = IdType;

	enum class WorkerState
	{
		Idle,
		MovingToJob,
		WorkingJob,
		Wander
	};

	struct WorkerInstance
	{
		WorkerId Id;
		WorkerPrototypeId prototypeId;
		IdType allocatedJobId;
		sf::Vector2f position;
		WorkerState state;

		// TODO: Wander state struct???
		sf::Vector2f wanderTarget;
		float idleTime{ 0.0f };
		float wanderBackoff{ 0.0f };
	};

	struct WorkerPrototype
	{
		std::string name;
		std::unordered_set<std::string> validJobPrototypes;
		// TODO: Consistency about string/IdType
	};
}