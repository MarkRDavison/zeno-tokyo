#pragma once

#include <tokyo/Bees/World/Region.hpp>

namespace bee
{

	class Level
	{
	public:
		Level();

		const int RegionWidth = 4;
		const int RegionHeight = 2;

		const std::vector<Entity*>& getEntities() const;
		const std::vector<Region*>& getRegions() const;

		void addEntity(Entity* entity);
		void addRegion(Region* region);

		void update(float delta);

		const Tile& getTile(int x, int y) const;
		Tile& getTile(int x, int y);

		bool tileExists(int x, int y) const;

		Entity* getEntityAtTile(int x, int y) const;

	private:
		std::vector<Region*> _regions;
		std::vector<Entity*> _entities;
		std::vector<Entity*> _entitiesToAdd;
	};

}