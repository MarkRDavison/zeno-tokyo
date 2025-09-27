#pragma once

namespace sol
{
	class state;
}

namespace drl
{
	class CoreUserData
	{
		CoreUserData() = delete;
		~CoreUserData() = delete;
	public:
		static void generateInfrastructureUserData(sol::state& _state);
	};
}