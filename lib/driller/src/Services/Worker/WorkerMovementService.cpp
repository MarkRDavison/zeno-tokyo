#include <tokyo/Driller/Services/Worker/WorkerMovementService.hpp>

#include <tokyo/Core/Utils/VectorMath.hpp>

namespace drl
{
WorkerMovementService::WorkerMovementService(
		WorkerData& _workerData,
		const JobData& _jobData,
		const ITerrainAlterationService& _terrainAlterationService
	) :
		m_WorkerData(_workerData),
		m_JobData(_jobData),
		m_TerrainAlterationService(_terrainAlterationService)
	{

	}

	void WorkerMovementService::update(float _delta) {
		for (auto& w : m_WorkerData.workers) {
			updateWorker(_delta, w);
		}
	}

	bool moveTowardsTarget(float _speed, float _delta, WorkerInstance& _worker, sf::Vector2f _target) {
		const float distanceToTarget = tokyo::distance(_worker.position, _target);
		const float maxMovement = _delta * _speed;

		if (distanceToTarget <= maxMovement) {
			_worker.position = _target;
			// TODO: update with remaining delta
			return true;
		}

		_worker.position += tokyo::normalise(_target - _worker.position) * maxMovement;
		return false;
	}

	void WorkerMovementService::updateIdleWorker(float _delta, WorkerInstance& _worker) {
		constexpr float WanderStartTime = 2.5f;
		if (_worker.allocatedJobId > 0) 
		{
			_worker.state = WorkerState::MovingToJob;
			updateWorker(_delta, _worker);
		}
		else
		{
			_worker.idleTime += _delta;
			if (_worker.idleTime > WanderStartTime * _worker.wanderBackoff)
			{
				const int range = 5;
				const int offset = (rand() % range) - (range - 1) / 2;

				if (offset != 0)
				{
					auto pos = _worker.position.x + (float)offset;
					const float tileX = static_cast<int>(pos < 0.0f
						? std::floor(pos + 0.5f)
						: std::ceil(pos - 0.5f));
					const float tileY = static_cast<int>(_worker.position.y - 1);

					if (m_TerrainAlterationService.canTileBeReached(tileY, tileX))
					{
						_worker.wanderTarget = { tileX, _worker.position.y };
						_worker.wanderBackoff = 1.0f;
						_worker.state = WorkerState::Wander;
						updateWorker(_delta, _worker);
					}
					else
					{
						_worker.wanderBackoff += 1.0f;
					}
				}

			}
		}
	}

	void WorkerMovementService::updateMovingToJobWorker(float _delta, WorkerInstance& _worker) {
		const auto& jobIter = std::find_if(m_JobData.jobs.begin(), m_JobData.jobs.end(),
			[&_worker](const JobInstance& _j) -> bool {
				return _j.allocatedWorkerId == _worker.Id;
			}
		);

		assert(jobIter != m_JobData.jobs.end());

		const auto& job = *jobIter;

		const sf::Vector2f jobPos = sf::Vector2f(job.tile) + sf::Vector2f(0.0f, 1.0f) + job.offset;
		sf::Vector2f pos = jobPos;

		if (pos.y != _worker.position.y) {
			// We are not on the same level
			if (_worker.position.x != 0.0f) {
				// We need to move to the elevator
				pos = { 0.0f, _worker.position.y };
			}
			else {
				// We are on the elevator
				pos = { 0.0f, pos.y };
			}
		}

		if (moveTowardsTarget(1.0f, _delta, _worker, pos) && jobPos == _worker.position) {
			_worker.state = WorkerState::WorkingJob;
		}
	}

	void WorkerMovementService::updateWanderingWorker(float _delta, WorkerInstance& _worker)
	{
		if (_worker.allocatedJobId != 0)
		{
			updateIdleWorker(_delta, _worker);
			return;
		}

		if (moveTowardsTarget(0.5f, _delta, _worker, _worker.wanderTarget) && _worker.wanderTarget == _worker.position)
		{
			_worker.state = WorkerState::Idle;
			_worker.idleTime = 0.0f;
		}
	}

	void WorkerMovementService::updateWorker(float _delta, WorkerInstance& _worker) {
		switch (_worker.state) {
		case WorkerState::Idle:
			updateIdleWorker(_delta, _worker);
			break;
		case WorkerState::MovingToJob:
			updateMovingToJobWorker(_delta, _worker);
			break;
		case WorkerState::Wander:
			updateWanderingWorker(_delta, _worker);
			break;
		case WorkerState::WorkingJob:
			break;
		default:
			throw std::runtime_error("Invalid WorkerState");
		}
	}
}