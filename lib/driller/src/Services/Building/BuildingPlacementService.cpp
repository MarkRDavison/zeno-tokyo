#include <tokyo/Driller/Services/Building/BuildingPlacementService.hpp>

namespace drl
{

	BuildingPlacementService::BuildingPlacementService(
		BuildingData& _buildingData,
		ITerrainAlterationService& _terrainAlterationService,
		IWorkerRecruitmentService& _workerRecruitmentService,
		IJobCreationService& _jobCreationService,
		const IBuildingPrototypeService& _buildingPrototypeService
	) :
		m_BuildingData(_buildingData),
		m_TerrainAlterationService(_terrainAlterationService),
		m_WorkerRecruitmentService(_workerRecruitmentService),
		m_JobCreationService(_jobCreationService),
		m_BuildingPrototypeService(_buildingPrototypeService)
	{

	}

	bool BuildingPlacementService::canPlacePrototype(BuildingPrototypeId _prototypeId, int _level, int _column) const
	{
		if (!m_BuildingPrototypeService.isPrototypeRegistered(_prototypeId))
		{
			return false;
		}

		const BuildingPrototype& prototype = m_BuildingPrototypeService.getPrototype(_prototypeId);

		const int maxLevel = _level + static_cast<int>(prototype.size.y);
		const int maxCol = _column + static_cast<int>(prototype.size.x);

		for (int level = _level; level < maxLevel; ++level)
		{
			for (int col = _column; col < maxCol; ++col)
			{
				if (!m_TerrainAlterationService.doesTileExist(level, col))
				{
					return false;
				}
				const auto& tile = m_TerrainAlterationService.getTile(level, col);
				if (!tile.dugOut)
				{
					return false;
				}
				if (tile.jobReserved)
				{
					return false;
				}
				if (tile.hasBuilding)
				{
					return false;
				}
			}
		}

		return true;
	}

	bool BuildingPlacementService::placePrototype(BuildingPrototypeId _prototypeId, int _level, int _column)
	{
		if (!canPlacePrototype(_prototypeId, _level, _column))
		{
			return false;
		}

		const BuildingPrototype& prototype = m_BuildingPrototypeService.getPrototype(_prototypeId);

		m_BuildingData.buildings.emplace_back(m_BuildingPrototypeService.createInstanceById(_prototypeId));

		auto& instance = m_BuildingData.buildings.back();

		instance.coordinates = {
			_column, _level
		};

		if (!prototype.requiredWorkers.empty())
		{
			for (const auto& [workerPrototypeName, amount] : prototype.requiredWorkers)
			{
				m_WorkerRecruitmentService.registerWorkerPrototypeRequirement(workerPrototypeName, amount);
			}
		}

		for (int y = instance.coordinates.y; y <= instance.coordinates.y + prototype.size.y - 1; ++y)
		{
			for (int x = instance.coordinates.x; x <= instance.coordinates.x + prototype.size.x - 1; ++x)
			{
				auto& tile = m_TerrainAlterationService.getTile(y, x);
				tile.hasBuilding = true;
			}
		}

		for (const auto& providedJob : prototype.providedJobs)
		{
			if (!m_JobCreationService.createJob(providedJob.first, providedJob.second, { _column, _level }))
			{
				throw std::runtime_error("Failed to create job");
			}
		}

		return true;
	}

}