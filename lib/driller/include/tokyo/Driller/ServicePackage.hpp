#pragma once

#include <tokyo/Driller/ManagerPackage.hpp>
#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Driller/Services/GameCommandService.hpp>
#include <tokyo/Game/Resource/ResourceService.hpp>
#include <tokyo/Game/Entity/IdentityService.hpp>
#include <tokyo/Driller/Services/Building/BuildingPrototypeService.hpp>
#include <tokyo/Driller/Services/Job/JobPrototypeService.hpp>
#include <tokyo/Driller/Services/Job/JobAllocationService.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttlePrototypeService.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttleScheduleService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerMovementService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerJobUpdateService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerRecruitmentService.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>

namespace drl
{
	class ServicePackage
	{
	public:
		ServicePackage(
			ManagerPackage& _managers, 
			GameData& _gameData
		) :
			resourceService(),
			identificationService(),
			terrainAlterationService(_gameData.terrain),
			workerPrototypeService(identificationService),
			workerCreationService(_gameData.worker, workerPrototypeService),
			workerMovementService(_gameData.worker, _gameData.job, terrainAlterationService),
			workerJobUpdateService(_gameData.worker, _gameData.job, terrainAlterationService, jobPrototypeService),
			workerRecruitmentService(_gameData.worker, workerPrototypeService),
			shuttlePrototypeService(identificationService),
			shuttleScheduleService(_gameData.shuttle, workerRecruitmentService, workerCreationService, shuttlePrototypeService),
			shuttleCreationService(_gameData.shuttle, shuttlePrototypeService),
			jobPrototypeService(identificationService),
			jobAllocationService(_gameData.job, _gameData.worker, terrainAlterationService, workerPrototypeService),
			jobCreationService(_gameData.job, jobPrototypeService, terrainAlterationService),
			buildingPrototypeService(identificationService),
			buildingPlacementService(_gameData.building, terrainAlterationService, workerRecruitmentService, jobCreationService, buildingPrototypeService),
			gameCommandService(terrainAlterationService, workerCreationService, shuttleCreationService, buildingPlacementService, resourceService)
		{

		}

		tokyo::ResourceService resourceService;
		tokyo::IdentificationService<IdType> identificationService;

		TerrainAlterationService terrainAlterationService;

		WorkerPrototypeService workerPrototypeService;
		WorkerMovementService workerMovementService;
		WorkerCreationService workerCreationService;
		WorkerJobUpdateService workerJobUpdateService;
		WorkerRecruitmentService workerRecruitmentService;

		ShuttlePrototypeService shuttlePrototypeService;
		ShuttleScheduleService shuttleScheduleService;
		ShuttleCreationService shuttleCreationService;

		JobPrototypeService jobPrototypeService;
		JobAllocationService jobAllocationService;
		JobCreationService jobCreationService;

		BuildingPrototypeService buildingPrototypeService;
		BuildingPlacementService buildingPlacementService;

		GameCommandService gameCommandService;
	};
}