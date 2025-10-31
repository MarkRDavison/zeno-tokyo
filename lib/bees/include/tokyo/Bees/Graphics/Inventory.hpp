#pragma once

#include <tokyo/Bees/World/Entities/Player.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace bee
{

	class Inventory 
	{
	public:
		void draw(Player *player, sf::RenderTarget& target, sf::RenderStates states) const;
	};

}