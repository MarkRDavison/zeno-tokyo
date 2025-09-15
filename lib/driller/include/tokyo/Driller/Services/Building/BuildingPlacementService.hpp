#pragma once

#include <tokyo/Driller/Entities/Data/BuildingData.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerRecruitmentService.hpp>
#include <tokyo/Driller/Services/Job/JobCreationService.hpp>
#include <tokyo/Driller/Services/Building/BuildingPrototypeService.hpp>

namespace drl
{

	class IBuildingPlacementService
	{
	public:
		virtual ~IBuildingPlacementService(void) = 0;

		virtual bool canPlacePrototype(BuildingPrototypeId _prototypeId, int _level, int _column) const = 0;
		virtual bool placePrototype(BuildingPrototypeId _prototypeId, int _level, int _column) = 0;
	};

	inline IBuildingPlacementService::~IBuildingPlacementService(void) = default;

	class BuildingPlacementService : public IBuildingPlacementService
	{
	public:
		BuildingPlacementService(
			BuildingData& _buildingData,
			ITerrainAlterationService& _terrainAlterationService,
			IWorkerRecruitmentService& _workerRecruitmentService,
			IJobCreationService& _jobCreationService,
			const IBuildingPrototypeService& _buildingPrototypeService
		);
		~BuildingPlacementService(void) override = default;

		bool canPlacePrototype(BuildingPrototypeId _prototypeId, int _level, int _column) const override;
		bool placePrototype(BuildingPrototypeId _prototypeId, int _level, int _column) override;

	private:
		BuildingData& m_BuildingData;
		ITerrainAlterationService& m_TerrainAlterationService;
		IWorkerRecruitmentService& m_WorkerRecruitmentService;
		IJobCreationService& m_JobCreationService;
		const IBuildingPrototypeService& m_BuildingPrototypeService;
	};

}