#include <tokyo/Driller/Scripting/ResourceParser.hpp>
#include <tokyo/Driller/Scripting/ScriptingConstants.hpp>
#include <tokyo/Core/Utils/String.hpp>
#include <sol/sol.hpp>

namespace drl
{
	std::vector<tokyo::LevelResource> ResourceParser::parse(sol::state& _state) const
	{
		std::vector<tokyo::LevelResource> p;

		const sol::table& resources = _state[ScriptingConstants::Resources_ScriptRoot];
		for (const auto& kv : resources)
		{
			const sol::table table = kv.second;

			p.emplace_back(
				tokyo::Resource(
					(tokyo::ResourceId)tokyo::String::fnv1a_32(table["name"].get<std::string>()),
					table["amount"].get<tokyo::ResourceValue>()
				),
				table["max"].get<tokyo::ResourceValue>());
		}

		return p;
	}

}