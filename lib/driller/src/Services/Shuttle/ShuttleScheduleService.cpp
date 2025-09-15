#include <tokyo/Driller/Services/Shuttle/ShuttleScheduleService.hpp>
#include <tokyo/Core/Utils/VectorMath.hpp>

namespace drl
{

	ShuttleScheduleService::ShuttleScheduleService(
		ShuttleData& _shuttleData,
		IWorkerRecruitmentService& _workerRecruitmentService,
		IWorkerCreationService& _workerCreationService,
		const IShuttlePrototypeService& _shuttlePrototypeService
	) :
		m_ShuttleData(_shuttleData),
		m_WorkerRecruitmentService(_workerRecruitmentService),
		m_WorkerCreationService(_workerCreationService),
		m_ShuttlePrototypeService(_shuttlePrototypeService)
	{

	}

	void ShuttleScheduleService::update(float _delta)
	{
		for (auto& s : m_ShuttleData.shuttles)
		{
			updateShuttle(_delta, s, m_ShuttlePrototypeService.getPrototype(s.prototypeId));
		}
	}

	void ShuttleScheduleService::updateShuttle(float _delta, ShuttleInstance& _shuttle, const ShuttlePrototype& _prototype)
	{
		_shuttle.elapsed += _delta;
		switch (_shuttle.state)
		{
		case ShuttleState::Idle:
			if (_shuttle.elapsed >= _prototype.idleTime)
			{
				_shuttle.state = ShuttleState::TravellingToSurface;
				_shuttle.elapsed = 0.0f;
			}
			break;
		case ShuttleState::TravellingToSurface:
			if (moveShuttleTowardsLocation(_delta, _shuttle, _prototype, _shuttle.surfacePosition, ShuttleState::WaitingOnSurface))
			{
				const auto& requiredWorkerPrototypes = m_WorkerRecruitmentService.getRequiredWorkerTypes();
				for (const auto prototypeId : requiredWorkerPrototypes)
				{
					const auto amountRequired = m_WorkerRecruitmentService.getRequiredWorkerCount(prototypeId);
					m_WorkerRecruitmentService.reduceWorkerPrototypeRequirement(prototypeId, amountRequired);
					for (int i = 0; i < amountRequired; ++i)
					{
						if (!m_WorkerCreationService.createWorker(prototypeId, _shuttle.position))
						{
							m_WorkerRecruitmentService.registerWorkerPrototypeRequirement(prototypeId, 1);
						}
					}
				}
			}
			break;
		case ShuttleState::WaitingOnSurface:
			if (_shuttle.elapsed >= _prototype.loadingTime)
			{
				_shuttle.state = ShuttleState::LeavingSurface;
				_shuttle.elapsed = 0.0f;
			}
			break;
		case ShuttleState::LeavingSurface:
			moveShuttleTowardsLocation(_delta, _shuttle, _prototype, _shuttle.leavingPosition, ShuttleState::Completed);
			break;
		case ShuttleState::Completed:
			_shuttle.state = ShuttleState::Idle;
			_shuttle.position = _shuttle.startingPosition;
			break;
		default:
			throw std::runtime_error("Invalid shuttle state");
		}
	}

	bool ShuttleScheduleService::moveShuttleTowardsLocation(float _delta, ShuttleInstance& _shuttle, const ShuttlePrototype& _prototype, sf::Vector2f _target, ShuttleState _nextState)
	{
		const float distanceToTarget = tokyo::distance(_shuttle.position, _target);
		const float maxMovement = _prototype.speed * _delta;

		if (distanceToTarget <= maxMovement)
		{
			_shuttle.state = _nextState;
			_shuttle.position = _target;
			_shuttle.elapsed = 0.0f;
			return true;
		}

		_shuttle.position += tokyo::normalise(_target - _shuttle.position) * maxMovement;
		return false;
	}

}