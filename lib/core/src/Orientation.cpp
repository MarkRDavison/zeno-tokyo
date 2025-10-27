#include <tokyo/Core/Orientation.hpp>
#include <stdexcept>

namespace tokyo
{
	sf::Vector2i OrientationHelpers::toDirection(Orientation orientation)
	{
		switch (orientation)
		{
		case Orientation::NORTH:
			return { 0,-1 };
		case Orientation::EAST:
			return { 1,0 };
		case Orientation::SOUTH:
			return { 0,1 };
		case Orientation::WEST:
			return { -1,0 };
		default:
			return {};
		}
	}

	Orientation OrientationHelpers::fromDirection(const sf::Vector2i& direction)
	{
		if (direction.x == 0 && direction.y == -1)
		{
			return Orientation::NORTH;
		}
		else if (direction.x == 1 && direction.y == 0)
		{
			return Orientation::EAST;
		}
		else if (direction.x == 0 && direction.y == 1)
		{
			return Orientation::SOUTH;
		}
		else if (direction.x == -1 && direction.y == 0)
		{
			return Orientation::WEST;
		}

		return Orientation::NONE;
	}

}