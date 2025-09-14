#pragma once

#include <tokyo/Driller/Entities/Data/WorkerData.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>

namespace drl
{
	class IWorkerCreationService
	{
	public:
		virtual ~IWorkerCreationService(void) = 0;

		virtual bool createWorker(WorkerPrototypeId _id, sf::Vector2f _position) = 0;
	};

	inline IWorkerCreationService::~IWorkerCreationService(void) = default;

	class WorkerCreationService : public IWorkerCreationService
	{
	public:
		WorkerCreationService(
			WorkerData& _workerData,
			const IWorkerPrototypeService& _workerPrototypeService
		);
		~WorkerCreationService(void) override = default;

		bool createWorker(WorkerPrototypeId _id, sf::Vector2f _position) override;

	private:
		WorkerData& m_WorkerData;
		const IWorkerPrototypeService& m_WorkerPrototypeService;
	};
}