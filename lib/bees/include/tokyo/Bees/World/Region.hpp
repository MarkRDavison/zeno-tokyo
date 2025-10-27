#pragma once

#include <tokyo/Bees/World/Tile.hpp>
#include <tokyo/Bees/World/Entities/Entity.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

namespace bee
{

	class Region
	{
	public:
		Region(int startX, int startY);

		const int StartX;
		const int StartY;

		const int Width = 16;
		const int Height = 16;

		const Tile& getTile(int x, int y) const;
		Tile& getTile(int x, int y);

		const std::vector<Entity*>& getEntities() const;

		void addEntity(Entity* entity);

		void update(float delta);

		sf::Color col{ sf::Color::Magenta };

	private:
		std::vector<std::vector<Tile>> _tiles;
		std::vector<Entity*> _entities;
		std::vector<Entity*> _entitiesToAdd;
	};

}