#include <tokyo/Driller/Services/Worker/WorkerCreationService.hpp>

namespace drl
{

	WorkerCreationService::WorkerCreationService(
		WorkerData& _workerData,
		const IWorkerPrototypeService& _workerPrototypeService
	) :
		m_WorkerData(_workerData),
		m_WorkerPrototypeService(_workerPrototypeService)
	{

	}

	bool WorkerCreationService::createWorker(WorkerPrototypeId _id, sf::Vector2f _position)
	{
		if (!m_WorkerPrototypeService.isPrototypeRegistered(_id))
		{
			return false;
		}
		
		m_WorkerData.workers.emplace_back(m_WorkerPrototypeService.createInstanceById(_id));

		auto& worker = m_WorkerData.workers.back();
		worker.position = _position;

		return true;
	}
}