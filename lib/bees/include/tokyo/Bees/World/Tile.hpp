#pragma once

#include <SFML/Graphics/Color.hpp>

namespace bee
{
	struct Tile
	{
		int X;
		int Y;
		sf::Color Color{ sf::Color::Green };
	};
}