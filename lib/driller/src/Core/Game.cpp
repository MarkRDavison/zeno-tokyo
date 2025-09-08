#include <tokyo/Driller/Core/Game.hpp>

namespace drl
{

	Game::Game(
		GameData& _gameData,
		tokyo::IInputManager& _inputManager,
		tokyo::IInputActionManager& _inputActionManager
	) :
		_gameData(_gameData),
		_inputManager(_inputManager),
		_inputActionManager(_inputActionManager)
	{

	}

	void Game::update(float _delta)
	{

	}
}