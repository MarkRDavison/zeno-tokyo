#pragma once

#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Driller/Services/Job/JobAllocationService.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttleScheduleService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerMovementService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerJobUpdateService.hpp>

namespace drl
{

	class Game : public tokyo::NonCopyable
	{
	public:
		Game(
			GameData& _gameData,
			tokyo::IInputManager& _inputManager,
			tokyo::IInputActionManager& _inputActionManager,
			IShuttleScheduleService& _shuttleScheduleService,
			IJobAllocationService& _jobAllocationService,
			IWorkerMovementService& _workerMovementService,
			IWorkerJobUpdateService& _workerJobUpdateService
		);

		void update(float _delta);

	private:
		GameData& _gameData;

		tokyo::IInputManager& _inputManager;
		tokyo::IInputActionManager& _inputActionManager;

		IShuttleScheduleService& m_ShuttleScheduleService;
		IJobAllocationService& m_JobAllocationService;
		IWorkerMovementService& m_WorkerMovementService;
		IWorkerJobUpdateService& m_WorkerJobUpdateService;
	};

}