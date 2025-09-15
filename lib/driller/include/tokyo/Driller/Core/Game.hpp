#pragma once

#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Game/InputActionManager.hpp>
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
			IWorkerMovementService& _workerMovementService,
			IWorkerJobUpdateService& _workerJobUpdateService
		);

		void update(float _delta);

	private:
		GameData& _gameData;

		tokyo::IInputManager& _inputManager;
		tokyo::IInputActionManager& _inputActionManager;

		IWorkerMovementService& m_WorkerMovementService;
		IWorkerJobUpdateService& m_WorkerJobUpdateService;
	};

}