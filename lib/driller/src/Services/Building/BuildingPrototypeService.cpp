#include <tokyo/Driller/Services/Building/BuildingPrototypeService.hpp>

namespace drl
{

	BuildingPrototypeService::BuildingPrototypeService(
		tokyo::IIdentificationService<IdType>& _identificationService
	) :
		PrototypeService<BuildingPrototype, BuildingInstance, BuildingPrototypeId>(_identificationService)
	{

	}

	BuildingInstance BuildingPrototypeService::createInstance(const BuildingPrototype& _prototype) const
	{
		BuildingInstance Building{};
		Building.Id = m_IdentificationService.generateId();
		Building.prototypeId = getPrototypeId(_prototype.name);
		return Building;
	}

}