#include <tokyo/Driller/Orchestration.hpp>
#include <tokyo/Driller/Scenes/GameScene.hpp>
#include <tokyo/Driller/Scripting/EntityUserData.hpp>
#include <tokyo/Driller/Scripting/CoreUserData.hpp>
#include <tokyo/Driller/Scripting/PrototypeParser.hpp>
#include <tokyo/Driller/Scripting/ResourceParser.hpp>

namespace drl
{
	void Orchestration::InitialiseConfiguration(tokyo::Application& _app, ManagerPackage& _managers, ServicePackage& _services)
	{
		_managers.configManager.loadConfiguration("/data/Scripts/config.lua");

		auto& state = _managers.luaManager.getState(tokyo::LuaManager::DefaultStateScope);

		state.set_function("exit", &tokyo::Application::stop, &_app);
		state.set_function("cmd", &drl::GameCommandService::executeGameCommand, &_services.gameCommandService);

		drl::CoreUserData::generateInfrastructureUserData(state);
		drl::EntityUserData::generateEntitiesUserData(state);

		_managers.luaManager.runScriptFile("/data/Scripts/Base/prototypes.lua");
		{
			drl::PrototypeParser prototypeParser;
			const auto& parsedPrototypes = prototypeParser.parse(state);
			for (const auto& jp : parsedPrototypes.jobPrototypes)
			{
				_services.jobPrototypeService.registerPrototype(jp.name, jp);
				_services.identificationService.registerName(jp.name);
			}
			for (const auto& wp : parsedPrototypes.workerPrototypes)
			{
				_services.workerPrototypeService.registerPrototype(wp.name, wp);
				_services.identificationService.registerName(wp.name);
			}
			for (const auto& sp : parsedPrototypes.shuttlePrototypes)
			{
				_services.shuttlePrototypeService.registerPrototype(sp.name, sp);
				_services.identificationService.registerName(sp.name);
			}
			for (const auto& bp : parsedPrototypes.buildingPrototypes)
			{
				_services.buildingPrototypeService.registerPrototype(bp.name, bp);
				_services.identificationService.registerName(bp.name);
			}
		}

		_managers.luaManager.runScriptFile("/data/Scripts/Base/resources.lua");
		{
			drl::ResourceParser resourceParser;
			const auto& parsedResources = resourceParser.parse(state);
			for (const auto& r : parsedResources)
			{
				_services.resourceService.setResourceMaximum(r.resource.id, r.max);
				_services.resourceService.setResource(r.resource.id, r.resource.amount);
			}
		}
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
		// TODO: Need control mapping system and store mappings as config with default set
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

	void Orchestration::InitialiseGame(tokyo::Application& _app, drl::GameData& _gameData, ManagerPackage& _managers, ServicePackage& _services)
	{
		_managers.luaManager.runScriptFile("/data/Scripts/Base/initializeCommands.lua");

		auto scene = new drl::GameScene(
			_gameData,
			_managers.inputManager,
			_managers.inputActionManager,
			_managers.configManager,
			_managers.textureManager,
			_services.gameCommandService,
			_services.workerPrototypeService,
			_services.workerMovementService,
			_services.workerJobUpdateService);
		
		scene->start();
		_app.setScene(scene);
		_app.setAppSpeedMultiplier(4.0f); 

	}
}