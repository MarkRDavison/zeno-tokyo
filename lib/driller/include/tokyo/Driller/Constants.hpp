#pragma once

namespace drl
{
	// TODO: Lua doesn't like unsigned integers, so have to use signed as the result of string hashes
	using IdType = long long;

	class Constants
	{
	public:
		static constexpr const char Title[] = "Driller - Pre Alpha";

		static constexpr const char TileSpriteSheetTextureName[] = "TileSpriteSheetTextureName";
		static constexpr const char ClickActionName[] = "ClickActionName";
		static constexpr const char CancelActionName[] = "CancelActionName";
	};

}