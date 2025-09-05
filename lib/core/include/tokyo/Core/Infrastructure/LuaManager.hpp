#pragma once

#include <unordered_map>
#include <sol/sol.hpp>

namespace tokyo
{
	class LuaManager
	{
	public:

		static constexpr const char DefaultStateScope[] = "Default";

		LuaManager(void);
		virtual ~LuaManager(void);

		virtual void initialise();

		virtual void cleanup();

		virtual void runScriptFile(const std::string& _scriptPath);
		virtual void runScriptFile(const std::string& _scriptPath, const std::string& _scope);
		virtual void runScript(const std::string& _script);
		virtual void runScript(const std::string& _script, const std::string& _scope);

		virtual void createState(const std::string& _scope);
		virtual void deleteState(const std::string& _scope);

		virtual sol::state& getState(const std::string& _scope);

	private:
		bool _initialiseRan;
		bool _cleanupRan;

		sol::state _defaultScopeState;
		std::unordered_map<std::string, sol::state> _states;
	};
}