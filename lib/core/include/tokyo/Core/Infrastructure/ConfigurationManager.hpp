#pragma once

#include <string>

namespace tokyo
{
	class LuaManager;

	class IConfigurationManager
	{
	public:
		virtual ~IConfigurationManager(void) = 0;

		virtual std::pair<unsigned, unsigned> getResolution(void) const = 0;
		virtual std::string getTitle(void) const = 0;
		virtual float getGameViewScale(void) const = 0;
	};

	inline IConfigurationManager::~IConfigurationManager(void) = default;

	class ConfigurationManager : public IConfigurationManager
	{
	public:
		static constexpr const char ConfigStateScope[] = "Config";
		static constexpr const char DefaultTitle[] = "Tokyo Driller";

		static const constexpr unsigned int DefaultResolutionX = 1280;
		static const constexpr unsigned int DefaultResolutionY = 720;
		static const constexpr float DefaultGameViewScale = 50.0f;

		ConfigurationManager(LuaManager& _luaManager);
		~ConfigurationManager(void) = default;

		void loadConfiguration(const std::string& _configFilePath);
		void reloadConfiguration(void);

		std::pair<unsigned, unsigned> getResolution(void) const override;
		std::string getTitle(void) const override;
		float getGameViewScale(void) const override;

	private:
		float m_GameViewScale;
		unsigned int m_ResolutionX;
		unsigned int m_ResolutionY;
		std::string m_Title;

		std::string m_PreviousConfigFile;
		LuaManager& m_LuaManager;
	};
}