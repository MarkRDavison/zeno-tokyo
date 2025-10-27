#include <tokyo/Bees/World/Level.hpp>
#include <stdexcept>

namespace bee
{
	Level::Level()
	{

	}
	const std::vector<Entity*>& Level::getEntities() const
	{
		return _entities;
	}
	const std::vector<Region*>& Level::getRegions() const
	{
		return _regions;
	}

	void Level::addEntity(Entity* entity)
	{
		_entitiesToAdd.push_back(entity);
	}
	void Level::addRegion(Region* region)
	{
		_regions.push_back(region);
	}

	void Level::update(float delta)
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

	const Tile& Level::getTile(int x, int y) const
	{
		for (const auto& region : _regions)
		{
			if (region->StartX <= x && x < region->StartX + region->Width &&
				region->StartY <= y && y < region->StartY + region->Height) 
			{
				return region->getTile(x, y);
			}
		}

		throw std::runtime_error("Invalid tile coordinates");
	}

	Tile& Level::getTile(int x, int y)
	{
		for (const auto& region : _regions)
		{
			if (region->StartX <= x && x < region->StartX + region->Width &&
				region->StartY <= y && y < region->StartY + region->Height)
			{
				return region->getTile(x, y);
			}
		}

		throw std::runtime_error("Invalid tile coordinates");
	}
}