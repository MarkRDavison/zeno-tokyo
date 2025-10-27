#include <tokyo/Bees/World/Region.hpp>

namespace bee
{

	Region::Region(
		int startX, 
		int startY
	) :
		StartX(startX),
		StartY(startY)

	{
		for (int y = 0; y < Height; ++y)
		{
			_tiles.emplace_back();
			for (int x = 0; x < Width; ++x)
			{
				_tiles.back().push_back(Tile
					{
						.X = x + StartX,
						.Y = y + StartY
					});
			}
		}
	}


	const Tile& Region::getTile(int x, int y) const
	{
		return _tiles[y - StartY][x - StartX];
	}

	Tile& Region::getTile(int x, int y)
	{
		return _tiles[y - StartY][x - StartX];
	}

	const std::vector<Entity*>& Region::getEntities() const
	{
		return _entities;
	}

	void Region::addEntity(Entity* entity)
	{
		_entitiesToAdd.push_back(entity);
	}

	void Region::update(float delta)
	{
		for (auto e : _entities)
		{
			e->update(delta);
		}

		if (_entitiesToAdd.size() > 0)
		{
			for (auto e : _entitiesToAdd)
			{
				_entities.push_back(e);
			}

			_entitiesToAdd.clear();
		}
	}

}