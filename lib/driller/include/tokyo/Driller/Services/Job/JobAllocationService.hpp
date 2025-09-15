#pragma once

#include <tokyo/Driller/Entities/Data/JobData.hpp>
#include <tokyo/Driller/Entities/Data/WorkerData.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>

namespace drl
{

	class IJobAllocationService
	{
	public:
		virtual ~IJobAllocationService(void) = 0;

		virtual void allocateJobs(int _number = -1) = 0;
	};

	inline IJobAllocationService::~IJobAllocationService(void) = default;

	class JobAllocationService : public IJobAllocationService
	{
	public:
		JobAllocationService(
			JobData& _jobData,
			WorkerData& _workerData,
			const ITerrainAlterationService& _terrainAlterationService,
			const IWorkerPrototypeService& _workerPrototypeService
		);
		~JobAllocationService(void) override = default;

		void allocateJobs(int _number = -1) override;

		bool canWorkerPerformJob(const WorkerInstance& _worker, const JobInstance& _job) const;

	private:
		JobData& m_JobData;
		WorkerData& m_WorkerData;
		const ITerrainAlterationService& m_TerrainAlterationService;
		const IWorkerPrototypeService& m_WorkerPrototypeService;
	};

}