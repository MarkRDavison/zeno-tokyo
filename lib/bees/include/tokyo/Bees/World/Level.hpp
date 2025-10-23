#pragma once

#include <tokyo/Bees/World/Tile.hpp>
#include <tokyo/Bees/World/Entities/Entity.hpp>
#include <vector>

namespace bee
{

	class Level
	{
	public:
		Level();

		const int Width = 20;
		const int Height = 10;

		const Tile& getTile(int x, int y) const;

		const std::vector<Entity*>& getEntities() const;

		void addEntity(Entity* entity);

	private:
		std::vector<std::vector<Tile>> _tiles;
		std::vector<Entity*> _entities;

	};

}