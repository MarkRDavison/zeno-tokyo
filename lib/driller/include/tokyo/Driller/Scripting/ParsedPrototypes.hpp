#pragma once

#include <tokyo/Driller/Entities/Building.hpp>
#include <tokyo/Driller/Entities/Job.hpp>
#include <tokyo/Driller/Entities/Shuttle.hpp>
#include <tokyo/Driller/Entities/Worker.hpp>
#include <vector>

namespace drl
{

	struct ParsedPrototypes
	{
		std::vector<BuildingPrototype> buildingPrototypes;
		std::vector<JobPrototype> jobPrototypes;
		std::vector<ShuttlePrototype> shuttlePrototypes;
		std::vector<WorkerPrototype> workerPrototypes;
	};

}
