#pragma once

#include <SFML/System/Vector2.hpp>

namespace tokyo
{
	enum class Orientation
	{
		NONE,
		NORTH,
		EAST,
		SOUTH,
		WEST,
		UP = NORTH,
		RIGHT = EAST,
		DOWN = SOUTH,
		LEFT = WEST
	};

	class OrientationHelpers
	{
		OrientationHelpers() = delete;
	public:
		static sf::Vector2i toDirection(Orientation orientation);
		static Orientation fromDirection(const sf::Vector2i& direction);
	};
}