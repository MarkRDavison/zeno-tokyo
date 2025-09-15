#include <tokyo/Driller/Core/Game.hpp>

namespace drl
{

	Game::Game(
		GameData& _gameData,
		tokyo::IInputManager& _inputManager,
		tokyo::IInputActionManager& _inputActionManager,
		IWorkerMovementService& _workerMovementService,
		IWorkerJobUpdateService& _workerJobUpdateService
	) :
		_gameData(_gameData),
		_inputManager(_inputManager),
		_inputActionManager(_inputActionManager),
		m_WorkerMovementService(_workerMovementService),
		m_WorkerJobUpdateService(_workerJobUpdateService)
	{

	}

	void Game::update(float _delta)
	{
		m_WorkerMovementService.update(_delta);
		m_WorkerJobUpdateService.update(_delta);
	}
}