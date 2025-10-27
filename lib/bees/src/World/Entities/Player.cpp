#include <tokyo/Bees/World/Entities/Player.hpp>
#include <tokyo/Bees/World/Entities/Hive.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Bees/Constants.hpp>

namespace bee
{
	void Player::update(float)
	{
		auto& instance = BeeInstance::Get();

		if (instance.InputActionManager.isActionInvoked(Constants::Action_TEMP_PlaceHive))
		{

			if (auto activeLevel = BeeInstance::Get().ActiveLevel; activeLevel != nullptr)
			{
				auto offset = tokyo::OrientationHelpers::toDirection(this->_orientation);
				auto targetTileX = this->TileX + offset.x;
				auto targetTileY = this->TileY + offset.y;

				auto& targetTile = activeLevel->getTile(targetTileX, targetTileY);
				if (targetTile.Validity == TileValidity::CLEAR)
				{
					targetTile.Validity = TileValidity::OCCUPIED;

					auto h = new Hive();
					h->TileX = targetTileX;
					h->TileY = targetTileY;
					activeLevel->addEntity(h);
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

			const auto& targetTile = activeLevel->getTile(targetTileX, targetTileY);

			if (targetTile.Validity == TileValidity::CLEAR)
			{
				this->TileX = targetTileX;
				this->TileY = targetTileY;
			}
		}
	}
}