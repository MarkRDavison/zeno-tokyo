#pragma once

#include <tokyo/Game/Entity/PrototypeService.hpp>
#include <tokyo/Game/Entity/IdentityService.hpp>
#include <tokyo/Driller/Entities/Worker.hpp>

namespace drl
{
	using IWorkerPrototypeService = tokyo::IPrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>;

	class WorkerPrototypeService : public tokyo::PrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>
	{
	public:
		WorkerPrototypeService(tokyo::IIdentificationService<IdType>& _identificationService);
		~WorkerPrototypeService(void) override = default;

		WorkerInstance createInstance(const WorkerPrototype& _prototype) const override;
	};

}