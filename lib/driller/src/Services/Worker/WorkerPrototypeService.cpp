#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>

namespace drl
{

	WorkerPrototypeService::WorkerPrototypeService(
		tokyo::IIdentificationService<IdType>& _identificationService
	) :
		PrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>(_identificationService)
	{

	}

	WorkerInstance WorkerPrototypeService::createInstance(const WorkerPrototype& _prototype) const
	{
		WorkerInstance worker{};

		worker.Id = m_IdentificationService.generateId();
		worker.prototypeId = getPrototypeId(_prototype.name);
		worker.state = WorkerState::Idle;
		worker.idleTime = 0.0f;
		worker.wanderBackoff = 1.0f;

		return worker;
	}

}