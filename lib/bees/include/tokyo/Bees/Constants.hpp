#pragma once

namespace bee
{
	class Constants
	{
		Constants() = delete;
	public:
		static constexpr const char Title[] = "Bees - Pre Alpha";
		static constexpr const char Action_Left[] = "LEFT";
		static constexpr const char Action_Right[] = "RIGHT";
		static constexpr const char Action_Up[] = "UP";
		static constexpr const char Action_Down[] = "DOWN";
		static constexpr const char Action_TEMP_PlaceHive[] = "TEMP_PLACE_HIVE";
	};
}