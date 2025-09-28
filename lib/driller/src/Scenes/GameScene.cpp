#include <tokyo/Driller/Scenes/GameScene.hpp>
#include <SFML/Graphics.hpp>

namespace drl
{
	GameScene::GameScene(
		GameData& _gameData,
		tokyo::IInputActionManager& _inputActionManager,
		tokyo::FontManager& _fontManager,
		tokyo::TextureManager& _textureManager,
		const tokyo::IResourceService& _resourceService,
		GameCommandService& _gameCommandService,
		const IWorkerPrototypeService& _workerPrototypeService,
		const IShuttlePrototypeService& _shuttlePrototypeService,
		const IBuildingPrototypeService& _buildingPrototypeService,
		const IJobPrototypeService& _jobPrototypeService,
		IWorkerMovementService& _workerMovementService,
		IWorkerJobUpdateService& _workerJobUpdateService,
		IShuttleScheduleService& _shuttleScheduleService,
		IJobAllocationService& _jobAllocationService,
		ITerrainAlterationService& _terrainAlterationService,
		IUiService& _uiService
	) :
		m_GameData(_gameData),
		m_InputActionManager(_inputActionManager),
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_ResourceService(_resourceService),
		m_GameCommandService(_gameCommandService),
		m_WorkerPrototypeService(_workerPrototypeService),
		m_ShuttlePrototypeService(_shuttlePrototypeService),
		m_BuildingPrototypeService(_buildingPrototypeService),
		m_JobPrototypeService(_jobPrototypeService),
		m_WorkerMovementService(_workerMovementService),
		m_WorkerJobUpdateService(_workerJobUpdateService),
		m_ShuttleScheduleService(_shuttleScheduleService),
		m_JobAllocationService(_jobAllocationService),
		m_TerrainAlterationService(_terrainAlterationService),
		m_UiService(_uiService)
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
			m_ShuttleScheduleService,
			m_JobAllocationService,
			m_WorkerMovementService,
			m_WorkerJobUpdateService
		);

		m_GameRenderer = new GameRenderer(
			m_GameData,
			m_GameCommandService,
			m_FontManager,
			m_TextureManager,
			m_InputActionManager,
			m_ResourceService,
			m_WorkerPrototypeService,
			m_ShuttlePrototypeService,
			m_BuildingPrototypeService,
			m_JobPrototypeService,
			m_TerrainAlterationService,
			m_UiService
		);

		started = true;
	}

	void GameScene::update(float _delta) 
	{
		// const auto tick = m_GameCommandService.getCurrentTick();

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