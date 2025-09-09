#pragma once

#include <tokyo/Game/Entity/PrototypeService.hpp>
#include <tokyo/Game/Entity/IdentityService.hpp>
#include <tokyo/Driller/Entities/Building.hpp>

namespace drl
{

	class BuildingPrototypeService : public tokyo::PrototypeService<BuildingPrototype, BuildingInstance, BuildingPrototypeId>
	{
	public:
		BuildingPrototypeService(tokyo::IIdentificationService<IdType>& _identificationService);
		~BuildingPrototypeService(void) override = default;

		BuildingInstance createInstance(const BuildingPrototype& _prototype) const override;
	};

}