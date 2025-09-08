#pragma once

#include <tokyo/Driller/Scripting/IScriptParser.hpp>
#include <tokyo/Driller/Scripting/ParsedPrototypes.hpp>

namespace drl
{

	class PrototypeParser : public IScriptParser<ParsedPrototypes>
	{
	public:
		~PrototypeParser() override = default;

		ParsedPrototypes parse(sol::state& _state) const;
	};

}