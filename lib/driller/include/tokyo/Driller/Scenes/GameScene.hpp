#pragma once

#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Driller/Core/Game.hpp>
#include <tokyo/Driller/Core/GameRenderer.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Core/Infrastructure/ConfigurationManager.hpp>
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
			tokyo::ConfigurationManager& _configurationManager);
		void start() override;

		void update(float _delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		GameData& m_GameData;

		tokyo::IInputManager& m_InputManager;
		tokyo::IInputActionManager& m_InputActionManager;
		tokyo::ConfigurationManager& m_ConfigurationManager;

		Game* m_Game{ nullptr };
		GameRenderer* m_GameRenderer{ nullptr };
	};
}