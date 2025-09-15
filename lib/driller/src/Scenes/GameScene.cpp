#include <tokyo/Driller/Scenes/GameScene.hpp>
#include <SFML/Graphics.hpp>

namespace drl
{
	GameScene::GameScene(
		GameData& _gameData,
		tokyo::IInputManager& _inputManager,
		tokyo::IInputActionManager& _inputActionManager,
		tokyo::ConfigurationManager& _configurationManager,
		tokyo::TextureManager& _textureManager,
		GameCommandService& _gameCommandService,
		const WorkerPrototypeService& _workerPrototypeService,
		IWorkerMovementService& _workerMovementService,
		IWorkerJobUpdateService& _workerJobUpdateService
	) :
		m_GameData(_gameData),
		m_InputManager(_inputManager),
		m_InputActionManager(_inputActionManager),
		m_ConfigurationManager(_configurationManager),
		m_TextureManager(_textureManager),
		m_GameCommandService(_gameCommandService),
		m_WorkerPrototypeService(_workerPrototypeService),
		m_WorkerMovementService(_workerMovementService),
		m_WorkerJobUpdateService(_workerJobUpdateService)
	{

	}

	GameScene::~GameScene()
	{
		if (m_Game != nullptr)
		{
			delete m_Game;
		}
		if (m_GameRenderer != nullptr)
		{
			delete m_GameRenderer;
		}
	}

	void GameScene::start() 
	{
		m_Game = new Game(
			m_GameData,
			m_InputManager,
			m_InputActionManager,
			m_WorkerMovementService,
			m_WorkerJobUpdateService
		);

		m_GameRenderer = new GameRenderer(
			m_GameData,
			m_TextureManager,
			m_WorkerPrototypeService
		);

		started = true;
	}

	void GameScene::update(float _delta) 
	{
		const auto tick = m_GameCommandService.getCurrentTick();

		if (m_Game != nullptr)
		{
			m_Game->update(_delta);
		}

		if (m_GameRenderer != nullptr)
		{
			m_GameRenderer->update(_delta);
		}

		m_GameCommandService.tick();
		m_InputActionManager.updateCachedInputs();
	}

	void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		if (m_GameRenderer != nullptr)
		{
			m_GameRenderer->draw(target, states);
		}
	}

}