#pragma once

#include <tokyo/Driller/Entities/Data/JobData.hpp>
#include <tokyo/Driller/Entities/Data/WorkerData.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>
#include <tokyo/Driller/Services/Job/JobPrototypeService.hpp>

namespace drl
{
	class IWorkerJobUpdateService
	{
	public:
		virtual ~IWorkerJobUpdateService() = 0;

		virtual void update(float _delta) = 0;
	};

	inline IWorkerJobUpdateService::~IWorkerJobUpdateService() = default;

	class WorkerJobUpdateService final : public IWorkerJobUpdateService
	{
	public:
		WorkerJobUpdateService(
			WorkerData& _workerData,
			JobData& _jobData,
			ITerrainAlterationService& _terrainAlterationService,
			const IJobPrototypeService& _jobPrototypeService
		);
		~WorkerJobUpdateService() override = default;

		void update(float _delta) override;
		void updateWorkerJob(float _delta, WorkerInstance& _worker, JobInstance& _job) const;
		void removeCompletedJobs() const;

	private:
		WorkerData& m_WorkerData;
		JobData& m_JobData;
		ITerrainAlterationService& m_TerrainAlterationService;
		const IJobPrototypeService& m_JobPrototypeService;
	};
}