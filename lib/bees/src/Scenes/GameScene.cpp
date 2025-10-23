#include <tokyo/Bees/Scenes/GameScene.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Core/Log.hpp>

namespace bee
{
	void GameScene::start()
	{
		BeeInstance::Get().ActiveLevel = new Level();
		BeeInstance::Get().ActiveLevel->addEntity(new Entity
			{
				.TileX = 3,
				.TileY = 4
			});
		BeeInstance::Get().ActiveLevel->addEntity(new Entity
			{
				.TileX = 8,
				.TileY = 6
			});
	}

	void GameScene::update(float)
	{
		if (BeeInstance::Get().InputActionManager.isActionInvoked("LCLICK"))
		{
			tokyo::Log::Debug("LCLICK Invoked!\n");
		}

		if (BeeInstance::Get().InputActionManager.isActionInvoked("SPACE"))
		{
			tokyo::Log::Debug("SPACE Invoked!\n");
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
			sf::VertexArray tiles(sf::PrimitiveType::Triangles);

			for (int y = 0; y < activeLevel->Height; ++y)
			{
				for (int x = 0; x < activeLevel->Width; ++x)
				{
					auto& tile = activeLevel->getTile(x, y);

					tiles.append(sf::Vertex
						{
							.position = sf::Vector2f(SIZE * (x + 0), SIZE * (y + 0)),
							.color = tile.Color
						});
					tiles.append(sf::Vertex
						{
							.position = sf::Vector2f(SIZE * (x + 1), SIZE * (y + 0)),
							.color = tile.Color
						});
					tiles.append(sf::Vertex
						{
							.position = sf::Vector2f(SIZE * (x + 1), SIZE * (y + 1)),
							.color = tile.Color
						});

					tiles.append(sf::Vertex
						{
							.position = sf::Vector2f(SIZE * (x + 0), SIZE * (y + 0)),
							.color = sf::Color::Magenta
						});
					tiles.append(sf::Vertex
						{
							.position = sf::Vector2f(SIZE * (x + 1), SIZE * (y + 1)),
							.color = sf::Color::Magenta
						});
					tiles.append(sf::Vertex
						{
							.position = sf::Vector2f(SIZE * (x + 0), SIZE * (y + 1)),
							.color = sf::Color::Magenta
						});
				}
			}

			target.draw(tiles, states);

			for (const auto& e : activeLevel->getEntities())
			{
				sf::CircleShape c(SIZE / 2.0f);
				c.setFillColor(sf::Color::Red);
				c.setPosition(sf::Vector2f((float)e->TileX, (float)e->TileY) * SIZE);
				target.draw(c, states);
			}
		}
	}
}