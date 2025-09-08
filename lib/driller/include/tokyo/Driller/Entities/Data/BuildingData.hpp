#pragma once

#include <tokyo/Driller/Entities/Building.hpp>
#include <vector>

namespace drl
{

	struct BuildingData
	{
		std::vector<BuildingInstance> buildings;
	};

}