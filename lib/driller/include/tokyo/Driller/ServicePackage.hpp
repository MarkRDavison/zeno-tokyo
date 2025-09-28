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
#include <tokyo/Driller/Services/UiService.hpp>

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
			economyService(),
			terrainAlterationService(_gameData.terrain),
			workerPrototypeService(identificationService),
			workerMovementService(_gameData.worker, _gameData.job, terrainAlterationService),
			workerCreationService(_gameData.worker, workerPrototypeService),
			workerJobUpdateService(_gameData.worker, _gameData.job, terrainAlterationService, jobPrototypeService),
			workerRecruitmentService(_gameData.worker, workerPrototypeService),
			shuttlePrototypeService(identificationService),
			shuttleScheduleService(_gameData.shuttle, workerRecruitmentService, workerCreationService, shuttlePrototypeService, resourceService, economyService),
			shuttleCreationService(_gameData.shuttle, shuttlePrototypeService),
			jobPrototypeService(identificationService),
			jobAllocationService(_gameData.job, _gameData.worker, terrainAlterationService, workerPrototypeService),
			jobCreationService(_gameData.job, jobPrototypeService, terrainAlterationService),
			buildingPrototypeService(identificationService),
			buildingPlacementService(_gameData.building, terrainAlterationService, workerRecruitmentService, jobCreationService, buildingPrototypeService),
			upgradeService(_gameData.upgrade),
			uiService(_managers.inputActionManager, buildingPrototypeService),
			gameCommandService(terrainAlterationService, workerCreationService, shuttleCreationService, buildingPlacementService, jobCreationService, resourceService, upgradeService)
		{

		}

		tokyo::ResourceService resourceService;
		tokyo::IdentificationService<IdType> identificationService;

		EconomyService economyService;

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

		UpgradeService upgradeService;

		UiService uiService;

		GameCommandService gameCommandService;
	};
}