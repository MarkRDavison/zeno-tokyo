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
		std::unordered_map<std::string, std::string> texturesWithNames = 
		{
			// TODO: Load from file system inspection/config
			{
				"/data/Textures/tile_sprite_sheet.png",
				drl::Constants::TileSpriteSheetTextureName
			}
		};

		for (const auto& [path, name] : texturesWithNames)
		{
			if (!_managers.textureManager.loadTexture(path, name))
			{
				return false;
			}
		}

		return true;
	}

	bool Orchestration::InitialiseFonts(ManagerPackage& _managers)
	{
		std::unordered_map<std::string, std::string> fontsWithNames =
		{
			// TODO: Load from file system inspection/config
			{
				"/data/Fonts/arial.ttf", 
				"DEBUG"
			}
		};

		for (const auto& [path, name] : fontsWithNames)
		{
			if (!_managers.fontManager.loadFont(path, name))
			{
				return false;
			}
		}

		return true;
	}
	
	void Orchestration::InitialiseInput(ManagerPackage& _managers)
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