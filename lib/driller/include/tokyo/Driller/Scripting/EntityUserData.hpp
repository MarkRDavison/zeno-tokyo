#pragma once

namespace sol
{
	class state;
}

namespace drl
{
	class EntityUserData
	{
		EntityUserData() = delete;
		~EntityUserData() = delete;
	public:
		static void generateEntitiesUserData(sol::state& _state);
	};
}