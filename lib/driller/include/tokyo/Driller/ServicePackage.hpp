#pragma once

#include <tokyo/Driller/ManagerPackage.hpp>
#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Driller/Services/GameCommandService.hpp>
#include <tokyo/Game/Resource/ResourceService.hpp>
#include <tokyo/Game/Entity/IdentityService.hpp>
#include <tokyo/Driller/Services/Building/BuildingPrototypeService.hpp>
#include <tokyo/Driller/Services/Job/JobPrototypeService.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttlePrototypeService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>
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
			buildingPrototypeService(identificationService),
			jobPrototypeService(identificationService),
			shuttlePrototypeService(identificationService),
			workerPrototypeService(identificationService),
			workerCreationService(_gameData.worker, workerPrototypeService),
			gameCommandService(terrainAlterationService, workerCreationService)
		{

		}

		tokyo::ResourceService resourceService;
		tokyo::IdentificationService<IdType> identificationService;

		TerrainAlterationService terrainAlterationService;

		BuildingPrototypeService buildingPrototypeService;
		JobPrototypeService jobPrototypeService;
		ShuttlePrototypeService shuttlePrototypeService;
		WorkerPrototypeService workerPrototypeService;

		WorkerCreationService workerCreationService;

		GameCommandService gameCommandService;
	};
}