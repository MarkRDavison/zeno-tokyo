#include <tokyo/Core/Infrastructure/ConfigurationManager.hpp>
#include <tokyo/Core/Infrastructure/LuaManager.hpp>
#include <iostream>

namespace tokyo
{
	ConfigurationManager::ConfigurationManager(LuaManager& _luaManager) :
		m_GameViewScale(DefaultGameViewScale),
		m_ResolutionX(DefaultResolutionX),
		m_ResolutionY(DefaultResolutionY),
		m_Title(DefaultTitle),
		m_LuaManager(_luaManager)
	{
		m_LuaManager.createState(ConfigStateScope);
	}


	void ConfigurationManager::loadConfiguration(const std::string& _configFilePath)
	{
		m_PreviousConfigFile = _configFilePath;

		try
		{
			m_LuaManager.runScriptFile(_configFilePath, ConfigStateScope);
		}
		catch (std::exception& e)
		{
			std::cerr << "Failed to load config file " << _configFilePath << ": " << e.what() << std::endl;
			return;
		}

		auto& state = m_LuaManager.getState(ConfigStateScope);

		sol::optional<unsigned int> resolutionX = state["config"]["resolution"]["x"];
		if (sol::nullopt != resolutionX)
		{
			m_ResolutionX = resolutionX.value();
		}
		sol::optional<unsigned int> resolutionY = state["config"]["resolution"]["y"];
		if (sol::nullopt != resolutionY)
		{
			m_ResolutionY = resolutionY.value();
		}
		sol::optional<std::string> title = state["config"]["title"];
		if (sol::nullopt != title)
		{
			m_Title = title.value();
		}
		sol::optional<float> gameViewScale = state["config"]["gameViewScale"];
		if (sol::nullopt != gameViewScale)
		{
			m_GameViewScale = gameViewScale.value();
		}
	}
	void ConfigurationManager::reloadConfiguration(void)
	{
		loadConfiguration(m_PreviousConfigFile);
	}

	std::pair<unsigned, unsigned> ConfigurationManager::getResolution(void) const
	{
		return { m_ResolutionX, m_ResolutionY };
	}

	std::string ConfigurationManager::getTitle(void) const
	{
		return m_Title;
	}

	float ConfigurationManager::getGameViewScale(void) const
	{
		return m_GameViewScale;
	}

}
