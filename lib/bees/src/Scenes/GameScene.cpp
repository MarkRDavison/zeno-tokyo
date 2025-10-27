#include <tokyo/Bees/Scenes/GameScene.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Bees/World/Entities/Player.hpp>
#include <tokyo/Bees/World/Entities/Hive.hpp>
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
		player->TileX = 1;
		player->TileY = 1;
		BeeInstance::Get().ActiveLevel->addEntity(player);
	}

	void GameScene::update(float delta)
	{
		if (BeeInstance::Get().InputActionManager.isActionInvoked("LCLICK"))
		{
			tokyo::Log::Debug("LCLICK Invoked!\n");
		}

		if (BeeInstance::Get().InputActionManager.isActionInvoked("SPACE"))
		{
			tokyo::Log::Debug("SPACE Invoked!\n");
		}

		if (auto level = BeeInstance::Get().ActiveLevel; level != nullptr)
		{
			level->update(delta);
		}

		BeeInstance::Get().InputActionManager.updateCachedInputs();
	}

	void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		const sf::Vector2f size(target.getSize());
		const float SIZE = 64.0f;

		auto activeLevel = BeeInstance::Get().ActiveLevel;
		if (activeLevel != nullptr)
		{
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
					if (const Player* player = dynamic_cast<const Player*>(e))
					{
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
						c.setPosition(sf::Vector2f((float)e->TileX, (float)e->TileY) * SIZE);
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
		}
	}
}