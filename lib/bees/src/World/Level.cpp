#include <tokyo/Bees/World/Level.hpp>

namespace bee
{

	Level::Level()
	{
		for (int y = 0; y < Height; ++y)
		{
			_tiles.emplace_back();
			for (int x = 0; x < Width; ++x) 
			{
				_tiles.back().push_back(Tile
					{
						.X = x,
						.Y = y
					});
			}
		}
	}


	const Tile& Level::getTile(int x, int y) const
	{
		return _tiles[y][x];
	}

	const std::vector<Entity*>& Level::getEntities() const
	{
		return _entities;
	}

	void Level::addEntity(Entity* entity)
	{
		_entities.push_back(entity);
	}
}