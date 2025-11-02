#include <tokyo/Bees/Scenes/GameScene.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Bees/World/Entities/Player.hpp>
#include <tokyo/Bees/World/Entities/Hive.hpp>
#include <tokyo/Bees/Graphics/TimeOfDayCircle.hpp>
#include <tokyo/Core/Log.hpp>

namespace bee
{
	void GameScene::start()
	{
		BeeInstance::Get().ActiveLevel = new Level();

		{
			auto region = new Region(0, 0);
			region->col = sf::Color::Magenta;
			BeeInstance::Get().ActiveLevel->addRegion(region);
		}
		{
			auto region = new Region(16, 0);
			region->col = sf::Color::Red;
			BeeInstance::Get().ActiveLevel->addRegion(region);
		}

		auto player = new Player();
		player->getInventoryAtSlot(0).name = "Hive";
		player->getInventoryAtSlot(0).texture = "hive";
		player->getInventoryAtSlot(0).count = 2;
		player->getInventoryAtSlot(1).name = "Bee";
		player->getInventoryAtSlot(1).texture = "bee";
		player->getInventoryAtSlot(1).count = 6;
		player->TileX = 3;
		player->TileY = 3;
		BeeInstance::Get().ActiveLevel->addEntity(player);
	}

	void GameScene::update(float delta)
	{
		if (auto level = BeeInstance::Get().ActiveLevel; level != nullptr)
		{
			level->update(delta);
		}

		BeeInstance::Get().GameTime.update(delta);
		BeeInstance::Get().InputActionManager.updateCachedInputs();
	}

	void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		const float SIZE = 64.0f;

		auto activeLevel = BeeInstance::Get().ActiveLevel;
		if (activeLevel != nullptr)
		{
			Player* p = nullptr;

			for (const auto& region : activeLevel->getRegions())
			{
				sf::VertexArray tiles(sf::PrimitiveType::Triangles);

				for (int yRel = 0; yRel < region->Height; ++yRel)
				{
					for (int xRel = 0; xRel < region->Width; ++xRel)
					{
						auto x = xRel + region->StartX;
						auto y = yRel + region->StartY;

						auto& tile = region->getTile(x, y);

						auto color = tile.Color;

						if (tile.Validity != TileValidity::CLEAR)
						{
							color = sf::Color::Black;
						}

						tiles.append(sf::Vertex
							{
								.position = sf::Vector2f(SIZE * (x + 0), SIZE * (y + 0)),
								.color = color
							});
						tiles.append(sf::Vertex
							{
								.position = sf::Vector2f(SIZE * (x + 1), SIZE * (y + 0)),
								.color = color
							});
						tiles.append(sf::Vertex
							{
								.position = sf::Vector2f(SIZE * (x + 1), SIZE * (y + 1)),
								.color = color
							});

						tiles.append(sf::Vertex
							{
								.position = sf::Vector2f(SIZE * (x + 0), SIZE * (y + 0)),
								.color = region->col
							});
						tiles.append(sf::Vertex
							{
								.position = sf::Vector2f(SIZE * (x + 1), SIZE * (y + 1)),
								.color = region->col
							});
						tiles.append(sf::Vertex
							{
								.position = sf::Vector2f(SIZE * (x + 0), SIZE * (y + 1)),
								.color = region->col
							});
					}
				}

				target.draw(tiles, states);
			}

			for (const auto& e : activeLevel->getEntities())
			{
				if (e != nullptr)
				{
					if (Player* player = dynamic_cast<Player*>(e))
					{
						p = player;
						sf::CircleShape c(SIZE / 2.0f);
						c.setFillColor(sf::Color::Blue);
						c.setPosition(sf::Vector2f((float)e->TileX, (float)e->TileY) * SIZE);
						target.draw(c, states);

						auto direction = tokyo::OrientationHelpers::toDirection(player->_orientation);

						sf::CircleShape d(SIZE / 8.0f);
						d.setFillColor(sf::Color::Yellow);
						d.setPosition(sf::Vector2f(
							0.4f  + (float)e->TileX + direction.x / 2.0f,
							0.4f  + (float)e->TileY + direction.y / 2.0f) * SIZE);
						target.draw(d, states);

					}
					else if (const Hive* hive = dynamic_cast<const Hive*>(e))
					{
						sf::CircleShape c(SIZE / 2.0f);
						c.setFillColor(sf::Color::White);
						c.setPosition(sf::Vector2f((float)hive->TileX, (float)hive->TileY) * SIZE);
						target.draw(c, states);
					}
					else
					{
						sf::CircleShape c(SIZE / 2.0f);
						c.setFillColor(sf::Color::Red);
						c.setPosition(sf::Vector2f((float)e->TileX, (float)e->TileY) * SIZE);
						target.draw(c, states);
					}
				}
			}

			TimeOfDayCircle todc(48.0f, BeeInstance::Get().GameTime);

			auto s(states);
			s.transform.translate({ 64.0f, 64.0f });

			target.draw(todc, s);

			_inventory.draw(p, target, states);
		}
	}
}