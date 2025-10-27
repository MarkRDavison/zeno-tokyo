#pragma once

#include <SFML/Graphics/Color.hpp>

namespace bee
{
	enum class TileValidity
	{
		CLEAR = 0,
		OCCUPIED = 1 << 0,
		IMPASSABLE = 1 << 1
	};

	struct Tile
	{
		int X;
		int Y;
		sf::Color Color{ sf::Color::Green };
		
		TileValidity Validity{ TileValidity::CLEAR };
	};
}