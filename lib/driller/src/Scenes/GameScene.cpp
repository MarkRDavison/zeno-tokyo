#include <tokyo/Driller/Scenes/GameScene.hpp>

namespace drl
{
	GameScene::GameScene(
		GameData& _gameData,
		tokyo::IInputManager& _inputManager,
		tokyo::IInputActionManager& _inputActionManager,
		tokyo::ConfigurationManager& _configurationManager
	) :
		m_GameData(_gameData),
		m_InputManager(_inputManager),
		m_InputActionManager(_inputActionManager),
		m_ConfigurationManager(_configurationManager)
	{

	}

	void GameScene::start() {}
	void GameScene::update(float _delta) {}
	void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

}