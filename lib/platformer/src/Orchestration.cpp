#include <tokyo/Platformer/Orchestration.hpp>
#include <tokyo/Platformer/Constants.hpp>

namespace plt
{
	void Orchestration::InitialiseConfiguration(
		tokyo::Application& _app,
		tokyo::LuaManager& _luaManager,
		tokyo::ConfigurationManager& _configManager)
	{
		_configManager.loadConfiguration("/data/Scripts/config.lua");

		auto& state = _luaManager.getState(tokyo::LuaManager::DefaultStateScope);

		state.set_function("exit", &tokyo::Application::stop, &_app);

	}

	void Orchestration::InitialiseInput(
		tokyo::IInputActionManager& _inputActionManager)
	{
		{
			tokyo::InputAction action;
			action.primaryActivationType = tokyo::InputAction::InputActivationType::MouseButtonPress;
			action.primaryButton = sf::Mouse::Button::Left;
			_inputActionManager.registerAction(Constants::ClickActionName, action);
		}
	}

	void Orchestration::InitialiseFonts(
		tokyo::FontManager&)
	{

	}

	void Orchestration::InitialiseTextures(
		tokyo::TextureManager&)
	{

	}

	void Orchestration::InitialiseGame(
		PlatformerInstanceData& _instanceData)
	{
		_instanceData.clearColor = sf::Color::Green;
	}
}