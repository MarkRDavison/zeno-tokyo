#include <tokyo/Driller/Services/Job/JobAllocationService.hpp>
#include <limits>
#include <ranges>

namespace drl
{

	JobAllocationService::JobAllocationService(
		JobData& _jobData,
		WorkerData& _workerData,
		const ITerrainAlterationService& _terrainAlterationService,
		const IWorkerPrototypeService& _workerPrototypeService
	) :
		m_JobData(_jobData),
		m_WorkerData(_workerData),
		m_TerrainAlterationService(_terrainAlterationService),
		m_WorkerPrototypeService(_workerPrototypeService)
	{

	}

	void JobAllocationService::allocateJobs(int _number /*= -1*/)
	{
		int count = _number == -1 ? std::numeric_limits<int>::min() : -_number;
		const auto allocatableJobs = [](auto& j) -> bool { return j.allocatedWorkerId == 0; };
		const auto allocatableWorkers = [](auto& w) -> bool { return w.allocatedJobId == 0; };
		for (auto& job : m_JobData.jobs | std::views::filter(allocatableJobs))
		{
			for (auto& worker : m_WorkerData.workers | std::views::filter(allocatableWorkers))
			{
				if (canWorkerPerformJob(worker, job))
				{
					worker.allocatedJobId = job.Id;
					job.allocatedWorkerId = worker.Id;
					count++;
					if (count >= 0)
					{
						return;
					}
					break; // TODO: Add test
				}
			}
		}
	}

	bool JobAllocationService::canWorkerPerformJob(const WorkerInstance& _worker, const JobInstance& _job) const
	{
		if (!m_WorkerPrototypeService.isPrototypeRegistered(_worker.prototypeId))
		{
			return false;
		}
		const auto& workerPrototype = m_WorkerPrototypeService.getPrototype(_worker.prototypeId);

		bool valid = false;

		for (const auto& jobName : workerPrototype.validJobPrototypes)
		{
			const auto jobPrototypeId = m_WorkerPrototypeService.getPrototypeId(jobName);
			if (jobPrototypeId == _job.prototypeId)
			{
				valid = true;
				break;
			}
		}

		if (!valid)
		{
			return false;
		}

		if (!m_TerrainAlterationService.canTileBeReached(_job.tile.y, _job.tile.x))
		{
			return false;
		}

		return true;
	}
}