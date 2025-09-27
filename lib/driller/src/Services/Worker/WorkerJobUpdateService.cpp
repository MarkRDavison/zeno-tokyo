#include <tokyo/Driller/Services/Worker/WorkerJobUpdateService.hpp>
#include <tokyo/Core/Utils/VectorMath.hpp>
#include <algorithm>
#include <cassert>
#include <ranges>

namespace drl
{

    WorkerJobUpdateService::WorkerJobUpdateService(
        WorkerData& _workerData,
        JobData& _jobData,
        ITerrainAlterationService& _terrainAlterationService,
        const IJobPrototypeService& _jobPrototypeService
    ) :
        m_WorkerData(_workerData),
        m_JobData(_jobData),
        m_JobPrototypeService(_jobPrototypeService),
        m_TerrainAlterationService(_terrainAlterationService)
    {

    }

    bool filterJobWorkers(const WorkerInstance& _worker)
    {
        return _worker.state == WorkerState::WorkingJob;
    }

    void WorkerJobUpdateService::update(float _delta)
    {
        for (auto& w : m_WorkerData.workers | std::views::filter(filterJobWorkers))
        {
            updateWorkerJob(_delta, w, m_JobData.getJob(w.allocatedJobId));
        }

        removeCompletedJobs();
    }

    void WorkerJobUpdateService::updateWorkerJob(float _delta, WorkerInstance& _worker, JobInstance& _job) const
    {
        _job.work -= _delta;
        if (_job.work <= 0.0f)
        {
            const auto& prototype = m_JobPrototypeService.getPrototype(_job.prototypeId);

            if (prototype.repeats)
            {
                _job.work += prototype.work;
            }
            else
            {
                _job.requiresRemoval = true;
                _job.allocatedWorkerId = 0;
                _worker.allocatedJobId = 0;
                _worker.state = WorkerState::Idle;
                _worker.idleTime = 0.0f;
                auto& tile = m_TerrainAlterationService.getTile(_job.tile.y, _job.tile.x);
                tile.jobReserved = false;
            }

            if (prototype.onComplete)
            {
                prototype.onComplete(_job);
            }
        }
    }

    void WorkerJobUpdateService::removeCompletedJobs() const
    {
        std::erase_if(
            m_JobData.jobs,
            [](const JobInstance& _job) -> bool
            {
                return _job.requiresRemoval;
            }
        );
    }
}