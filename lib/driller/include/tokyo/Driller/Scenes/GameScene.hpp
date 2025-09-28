#pragma once

#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Driller/Core/Game.hpp>
#include <tokyo/Driller/Core/GameRenderer.hpp>
#include <tokyo/Driller/Services/GameCommandService.hpp>
#include <tokyo/Core/Infrastructure/ConfigurationManager.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Game/Scene.hpp>

namespace drl
{
	class GameScene : public tokyo::Scene
	{
	public:
		GameScene(
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
			IUiService& _uiService);
		~GameScene();

		void start() override;

		void update(float _delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		GameData& m_GameData;

		tokyo::IInputActionManager& m_InputActionManager;
		tokyo::FontManager& m_FontManager;
		tokyo::TextureManager& m_TextureManager;
		const tokyo::IResourceService& m_ResourceService;
		GameCommandService& m_GameCommandService;
		const IWorkerPrototypeService& m_WorkerPrototypeService;
		const IShuttlePrototypeService& m_ShuttlePrototypeService;
		const IBuildingPrototypeService& m_BuildingPrototypeService;
		const IJobPrototypeService& m_JobPrototypeService;
		IWorkerMovementService& m_WorkerMovementService;
		IWorkerJobUpdateService& m_WorkerJobUpdateService;
		IShuttleScheduleService& m_ShuttleScheduleService;
		IJobAllocationService& m_JobAllocationService;
		ITerrainAlterationService& m_TerrainAlterationService;
		IUiService& m_UiService;

		Game* m_Game{ nullptr };
		GameRenderer* m_GameRenderer{ nullptr };
	};
}