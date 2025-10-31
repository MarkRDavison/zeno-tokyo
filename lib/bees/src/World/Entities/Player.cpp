#include <tokyo/Bees/World/Entities/Player.hpp>
#include <tokyo/Bees/World/Entities/Hive.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Bees/Constants.hpp>
#include <algorithm>

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

				const auto& slot = getInventoryAtSlot(getActiveInventorySlot());

				if (activeLevel->tileExists(targetTileCoord.x, targetTileCoord.y))
				{
					// TODO: Replace with try get tile?
					auto& targetTile = activeLevel->getTile(targetTileCoord.x, targetTileCoord.y);
					if (slot.texture.empty())
					{
						if (targetTile.Validity == TileValidity::OCCUPIED)
						{
							auto e = activeLevel->getEntityAtTile(targetTileCoord.x, targetTileCoord.y);

							if (const Hive* hive = dynamic_cast<const Hive*>(e))
							{
								const auto& hiveInventory = hive->getInventory();

								std::cout << "TODO: Steal inventory" << std::endl;
							}
						}
					}
					else
					{
						if (slot.texture == "hive")
						{
							if (targetTile.Validity == TileValidity::CLEAR)
							{
								targetTile.Validity = TileValidity::OCCUPIED;

								auto h = new Hive(HiveType::Common, 3, 5);
								h->TileX = targetTileCoord.x;
								h->TileY = targetTileCoord.y;
								activeLevel->addEntity(h);
							}
						}
						else if (slot.texture == "bee")
						{
							if (targetTile.Validity == TileValidity::OCCUPIED)
							{
								auto e = activeLevel->getEntityAtTile(targetTileCoord.x, targetTileCoord.y);

								if (auto hive = dynamic_cast<Hive*>(e))
								{
									if (hive->addBee(BeeData
										{
											.species = "Honey",
											.productivity = 1.0f
										}))
									{
										tokyo::Log::Info("Added bee to hive!\n");
									}
									else
									{
										tokyo::Log::Warning("Failed to add bee to hive\n");
									}
								}
							}
						}
					}
				}
			}
		}

		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num1)) this->setActiveInventorySlot(0);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num2)) this->setActiveInventorySlot(1);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num3)) this->setActiveInventorySlot(2);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num4)) this->setActiveInventorySlot(3);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num5)) this->setActiveInventorySlot(4);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num6)) this->setActiveInventorySlot(5);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num7)) this->setActiveInventorySlot(6);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num8)) this->setActiveInventorySlot(7);
		if (instance.InputActionManager.isKeyDown(sf::Keyboard::Key::Num9)) this->setActiveInventorySlot(8);

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

	int Player::getActiveInventorySlot() const
	{
		return _slotIndex;
	}
	void Player::setActiveInventorySlot(int slotIndex)
	{
		_slotIndex = std::max(0, std::min(slotIndex, 8));
	}
	InventorySlot& Player::getInventoryAtSlot(int slotIndex)
	{
		return _inventory[slotIndex];
	}
	const InventorySlot& Player::getInventoryAtSlot(int slotIndex) const
	{
		return _inventory[slotIndex];
	}
}