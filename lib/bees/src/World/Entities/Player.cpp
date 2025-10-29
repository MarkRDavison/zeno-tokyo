#include <tokyo/Bees/World/Entities/Player.hpp>
#include <tokyo/Bees/World/Entities/Hive.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Bees/Constants.hpp>

namespace bee
{
	void Player::update(float)
	{
		auto& instance = BeeInstance::Get();

		if (instance.InputActionManager.isActionInvoked(Constants::Action_TEMP_Interact))
		{
			if (auto activeLevel = BeeInstance::Get().ActiveLevel; activeLevel != nullptr)
			{
				auto targetTileCoord = getFacedTile();

				// TODO: Replace with try get tile?
				if (activeLevel->tileExists(targetTileCoord.x, targetTileCoord.y))
				{
					auto& targetTile = activeLevel->getTile(targetTileCoord.x, targetTileCoord.y);

					if (targetTile.Validity == TileValidity::OCCUPIED)
					{
						auto e = activeLevel->getEntityAtTile(targetTileCoord.x, targetTileCoord.y);

						if (const Hive* hive = dynamic_cast<const Hive*>(e))
						{
							std::cout << "Hive at " << targetTileCoord.x << "," << targetTileCoord.y << std::endl;
							for (const auto& [k, v] : hive->getInventory())
							{
								std::cout << " - " << k << ": " << v << std::endl;
							}
						}
					}
				}
			}
		}

		if (instance.InputActionManager.isActionInvoked(Constants::Action_TEMP_PlaceHive))
		{

			if (auto activeLevel = BeeInstance::Get().ActiveLevel; activeLevel != nullptr)
			{
				auto targetTileCoord = getFacedTile();

				// TODO: Replace with try get tile?
				if (activeLevel->tileExists(targetTileCoord.x, targetTileCoord.y))
				{
					auto& targetTile = activeLevel->getTile(targetTileCoord.x, targetTileCoord.y);

					if (targetTile.Validity == TileValidity::CLEAR)
					{
						targetTile.Validity = TileValidity::OCCUPIED;

						auto h = new Hive(HiveType::Common, 3, 5);
						h->TileX = targetTileCoord.x;
						h->TileY = targetTileCoord.y;
						h->addBee(BeeData
							{
								.species = "Honey",
								.productivity = 1.0f
							});
						h->addBee(BeeData
							{
								.species = "Wax",
								.productivity = 0.25f
							});
						activeLevel->addEntity(h);
					}
				}

			}
		}

		sf::Vector2f offset = {};

		if (instance.InputActionManager.isActionInvoked(Constants::Action_Left))
		{
			offset.x -= 1.0f;
			_orientation = tokyo::Orientation::LEFT;
		}
		if (instance.InputActionManager.isActionInvoked(Constants::Action_Right))
		{
			offset.x += 1.0f;
			_orientation = tokyo::Orientation::RIGHT;
		}
		if (instance.InputActionManager.isActionInvoked(Constants::Action_Up))
		{
			offset.y -= 1.0f;
			_orientation = tokyo::Orientation::UP;
		}
		if (instance.InputActionManager.isActionInvoked(Constants::Action_Down))
		{
			offset.y += 1.0f;
			_orientation = tokyo::Orientation::DOWN;
		}

		if (auto activeLevel = BeeInstance::Get().ActiveLevel; activeLevel != nullptr)
		{
			auto targetTileX = this->TileX + (int)offset.x;
			auto targetTileY = this->TileY + (int)offset.y;

			if (activeLevel->tileExists(targetTileX, targetTileY))
			{
				const auto& targetTile = activeLevel->getTile(targetTileX, targetTileY);

				if (targetTile.Validity == TileValidity::CLEAR)
				{
					this->TileX = targetTileX;
					this->TileY = targetTileY;
				}
			}
		}
	}

	sf::Vector2i Player::getFacedTile() const
	{
		auto offset = tokyo::OrientationHelpers::toDirection(this->_orientation);
		auto targetTileX = this->TileX + offset.x;
		auto targetTileY = this->TileY + offset.y;

		return { targetTileX, targetTileY };
	}
}