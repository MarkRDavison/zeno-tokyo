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

namespace drl
{
	class ServicePackage
	{
	public:
		ServicePackage(
			ManagerPackage& _managers, 
			GameData& _gameData
		) :
			gameCommandService(),
			resourceService(),
			identificationService(),
			buildingPrototypeService(identificationService),
			jobPrototypeService(identificationService),
			shuttlePrototypeService(identificationService),
			workerPrototypeService(identificationService)
		{

		}

		GameCommandService gameCommandService;
		tokyo::ResourceService resourceService;
		tokyo::IdentificationService<IdType> identificationService;

		BuildingPrototypeService buildingPrototypeService;
		JobPrototypeService jobPrototypeService;
		ShuttlePrototypeService shuttlePrototypeService;
		WorkerPrototypeService workerPrototypeService;
	};
}