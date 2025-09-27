#pragma once

#include <unordered_map>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <sol/sol.hpp>

namespace tokyo
{
	class FileManager;

	class LuaManager : NonCopyable
	{
	public:

		static constexpr const char DefaultStateScope[] = "Default";

		LuaManager(const FileManager& _fileManager);
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

		const FileManager& m_FileManager;

		sol::state _defaultScopeState;
		std::unordered_map<std::string, sol::state> _states;
	};
}