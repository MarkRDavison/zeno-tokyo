#pragma once

#include <tokyo/Driller/Scripting/IScriptParser.hpp>
#include <tokyo/Game/Resource/Resource.hpp>
#include <vector>

namespace sol
{
	class state;
}

namespace drl
{
	class ResourceParser : public IScriptParser<std::vector<tokyo::LevelResource>>
	{
	public:
		~ResourceParser() override = default;

		std::vector<tokyo::LevelResource> parse(sol::state& _state) const override;
	};
}