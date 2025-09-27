#pragma once

#include <tokyo/Driller/Entities/Data/BuildingData.hpp>
#include <tokyo/Driller/Entities/Data/TerrainData.hpp>
#include <tokyo/Driller/Entities/Data/ShuttleData.hpp>
#include <tokyo/Driller/Entities/Data/WorkerData.hpp>
#include <tokyo/Driller/Entities/Data/JobData.hpp>
#include <tokyo/Driller/Entities/Data/UpgradeData.hpp>

namespace drl
{
	struct GameData
	{
		BuildingData building;
		ShuttleData shuttle;
		TerrainData terrain;
		WorkerData worker;
		JobData job;
		UpgradeData upgrade;
	};
}