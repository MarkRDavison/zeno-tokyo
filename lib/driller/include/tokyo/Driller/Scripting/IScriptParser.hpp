#pragma once

namespace sol
{
	class state;
}

namespace drl
{
	template<typename T>
	class IScriptParser
	{
	public:
		virtual ~IScriptParser(void);

		virtual T parse(sol::state& _state) const = 0;

	};

	template<typename T>
	inline IScriptParser<T>::~IScriptParser(void) = default;
}