#include <tokyo/Driller/Core/Game.hpp>

namespace drl
{

	Game::Game(
		IShuttleScheduleService& _shuttleScheduleService,
		IJobAllocationService& _jobAllocationService,
		IWorkerMovementService& _workerMovementService,
		IWorkerJobUpdateService& _workerJobUpdateService
	) :
		m_ShuttleScheduleService(_shuttleScheduleService),
		m_JobAllocationService(_jobAllocationService),
		m_WorkerMovementService(_workerMovementService),
		m_WorkerJobUpdateService(_workerJobUpdateService)
	{

	}

	void Game::update(float _delta)
	{
		m_ShuttleScheduleService.update(_delta);
		m_WorkerMovementService.update(_delta);
		m_WorkerJobUpdateService.update(_delta);
		m_JobAllocationService.allocateJobs(10);
	}
}