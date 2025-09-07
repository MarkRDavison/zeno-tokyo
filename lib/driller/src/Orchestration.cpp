#include <tokyo/Driller/Orchestration.hpp>

namespace drl
{
	void Orchestration::InitialiseConfiguration(tokyo::Application& _app, ManagerPackage& _managers)
	{
		_managers.configManager.loadConfiguration("/data/Scripts/config.lua");

		auto& state = _managers.luaManager.getState(tokyo::LuaManager::DefaultStateScope);

		state.set_function("exit", &tokyo::Application::stop, &_app);
	}
	
	bool Orchestration::InitialiseTextures(ManagerPackage& _managers)
	{
		return 
			_managers.textureManager.loadTexture(
				"./data/Textures/tile_sprite_sheet.png", 
				drl::Constants::TileSpriteSheetTextureName);
	}

	bool Orchestration::InitialiseFonts(ManagerPackage& _managers)
	{
		return 
			_managers.fontManager.loadFont(
				"/data/Fonts/arial.ttf", 
				"DEBUG");
	}
	
	bool Orchestration::InitialiseInput(ManagerPackage& _managers)
	{
		{
			tokyo::InputAction action;
			action.primaryActivationType = tokyo::InputAction::InputActivationType::MouseButtonPress;
			action.primaryButton = sf::Mouse::Button::Left;
			_managers.inputActionManager.registerAction(drl::Constants::ClickActionName, action);
		}
		{
			tokyo::InputAction action;
			action.primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress;
			action.primaryKey = sf::Keyboard::Key::Escape;
			_managers.inputActionManager.registerAction(drl::Constants::CancelActionName, action);
		}
	}
}