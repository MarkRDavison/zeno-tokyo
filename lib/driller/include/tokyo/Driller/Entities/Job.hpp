#pragma once

#include <tokyo/Driller/Constants.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <string>

namespace drl
{
	using JobPrototypeId = IdType;
	using JobId = IdType;

	struct JobInstance
	{
		JobId Id;
		JobPrototypeId prototypeId;
		IdType additionalPrototypeId;
		IdType allocatedWorkerId;
		sf::Vector2i tile;
		sf::Vector2f offset;
		bool requiresRemoval;
		float work;
	};

	struct JobPrototype
	{
		std::string name;
		bool repeats;
		float work;
		std::function<void(JobInstance)> onComplete;
		std::function<sf::Vector2f(JobInstance, JobPrototype)> calculateOffset;
	};

}