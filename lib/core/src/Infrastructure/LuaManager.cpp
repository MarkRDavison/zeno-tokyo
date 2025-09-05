#include <tokyo/Core/Infrastructure/LuaManager.hpp>

namespace tokyo
{
	int my_at_panic(lua_State* L)
	{
		std::cerr << sol::stack::get<std::string>(L, -1) << std::endl;
		return -1;
	}

	LuaManager::LuaManager(void) : 
		_initialiseRan(false),
		_cleanupRan(false)
	{
	}

	LuaManager::~LuaManager()
	{
		cleanup();
	}

	void LuaManager::initialise()
	{
		if (_initialiseRan)
		{
			return;
		}

		_initialiseRan = true;

		_defaultScopeState.open_libraries(sol::lib::base, sol::lib::string);
	}

	void LuaManager::cleanup()
	{
		if (_cleanupRan)
		{
			return;
		}

		_cleanupRan = true;
	}

	sol::state& LuaManager::getState(const std::string& _scope)
	{
		if (_scope == DefaultStateScope)
		{
			return _defaultScopeState;
		}

		if (const auto iterator = _states.find(_scope); iterator != _states.end())
		{
			return (*iterator).second;
		}

		throw std::runtime_error("Could not find LuaManager state for scope " + _scope);
	}

	void LuaManager::runScriptFile(const std::string& _scriptPath)
	{
		runScriptFile(_scriptPath, DefaultStateScope);
	}

	void LuaManager::runScriptFile(const std::string& _scriptPath, const std::string& _scope)
	{
		getState(_scope).script_file(_scriptPath);
	}

	void LuaManager::runScript(const std::string& _script)
	{
		runScript(_script, DefaultStateScope);
	}

	void LuaManager::runScript(const std::string& _script, const std::string& _scope)
	{
		getState(_scope).script(_script);
	}

	void LuaManager::createState(const std::string& _scope)
	{
		if (_states.find(_scope) != _states.end())
		{
			throw std::runtime_error("LuaManager state already exists for scope " + _scope);
		}

		auto stateIterator = _states.emplace(_scope, my_at_panic);
		sol::state& state = stateIterator.first->second;
		state.open_libraries(sol::lib::base, sol::lib::string);
	}

	void LuaManager::deleteState(const std::string& _scope)
	{
		const auto iterator = _states.find(_scope);
		if (iterator != _states.end())
		{
			lua_close(iterator->second);
			_states.erase(_scope);
			return;
		}

		throw std::runtime_error("LuaManager state does not exist for scope " + _scope);
	}
}