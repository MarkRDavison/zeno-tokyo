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
			tokyo::IInputManager& _inputManager,
			tokyo::IInputActionManager& _inputActionManager,
			tokyo::ConfigurationManager& _configurationManager,
			tokyo::TextureManager& _textureManager,
			const tokyo::IResourceService& _resourceService,
			GameCommandService& _gameCommandService,
			const IWorkerPrototypeService& _workerPrototypeService,
			const IShuttlePrototypeService& _shuttlePrototypeService,
			const IBuildingPrototypeService& _buildingPrototypeService,
			IWorkerMovementService& _workerMovementService,
			IWorkerJobUpdateService& _workerJobUpdateService,
			IShuttleScheduleService& _shuttleScheduleService,
			IJobAllocationService& _jobAllocationService);
		~GameScene();

		void start() override;

		void update(float _delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		GameData& m_GameData;

		tokyo::IInputManager& m_InputManager;
		tokyo::IInputActionManager& m_InputActionManager;
		tokyo::ConfigurationManager& m_ConfigurationManager;
		tokyo::TextureManager& m_TextureManager;
		const tokyo::IResourceService& m_ResourceService;
		GameCommandService& m_GameCommandService;
		const IWorkerPrototypeService& m_WorkerPrototypeService;
		const IShuttlePrototypeService& m_ShuttlePrototypeService;
		const IBuildingPrototypeService& m_BuildingPrototypeService;
		IWorkerMovementService& m_WorkerMovementService;
		IWorkerJobUpdateService& m_WorkerJobUpdateService;
		IShuttleScheduleService& m_ShuttleScheduleService;
		IJobAllocationService& m_JobAllocationService;

		Game* m_Game{ nullptr };
		GameRenderer* m_GameRenderer{ nullptr };
	};
}