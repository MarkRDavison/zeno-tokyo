#include <tokyo/Bees/Scenes/GameScene.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Core/Log.hpp>
#include <SFML/Graphics.hpp>

namespace bee
{

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

		states.transform.translate(size / 2.0f);

		sf::CircleShape c(96.0f);
		c.setOrigin({ c.getRadius(), c.getRadius() });
		c.setFillColor(sf::Color::Black);
		c.setOutlineColor(sf::Color::Cyan);
		c.setOutlineThickness(8.0f);

		target.draw(c, states);
	}
}