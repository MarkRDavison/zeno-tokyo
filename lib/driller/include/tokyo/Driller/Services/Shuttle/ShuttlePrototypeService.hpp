#pragma once

#include <tokyo/Game/Entity/PrototypeService.hpp>
#include <tokyo/Game/Entity/IdentityService.hpp>
#include <tokyo/Driller/Entities/Shuttle.hpp>

namespace drl
{
	using IShuttlePrototypeService = tokyo::IPrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>;

	class ShuttlePrototypeService : public tokyo::PrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>
	{
	public:
		ShuttlePrototypeService(tokyo::IIdentificationService<IdType>& _identificationService);
		~ShuttlePrototypeService(void) override = default;

		ShuttleInstance createInstance(const ShuttlePrototype& _prototype) const override;
	};

}