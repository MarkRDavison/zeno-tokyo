#pragma once

#include <tokyo/Driller/Entities/Data/JobData.hpp>
#include <tokyo/Driller/Entities/Data/WorkerData.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>

namespace drl
{
    class IWorkerMovementService {
    public:
        virtual ~IWorkerMovementService() = 0;

        virtual void update(float _delta) = 0;
    };

    inline IWorkerMovementService::~IWorkerMovementService(void) = default;

    class WorkerMovementService : public IWorkerMovementService {
    public:
        WorkerMovementService(
            WorkerData& _workerData,
            const JobData& _jobData,
            const ITerrainAlterationService& _terrainAlterationService
        );
        ~WorkerMovementService(void) override = default;

        void update(float _delta) override;
        void updateWorker(float _delta, WorkerInstance& _worker);

        void updateIdleWorker(float _delta, WorkerInstance& _worker);
        void updateMovingToJobWorker(float _delta, WorkerInstance& _worker);
        void updateWanderingWorker(float _delta, WorkerInstance& _worker);

    private:
        WorkerData& m_WorkerData;
        const JobData& m_JobData;
        const ITerrainAlterationService& m_TerrainAlterationService;
    };

}
