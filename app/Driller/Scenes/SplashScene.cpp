#include "SplashScene.hpp"
#include <SFML/Graphics.hpp>

namespace drl
{

	void SplashScene::Update(float delta)
	{

	}

	void SplashScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
        sf::RenderStates info(states);
        const sf::Vector2f size(target.getSize());

        info.transform.translate(size / 2.0f);

        sf::CircleShape c(96.0f);
        c.setOrigin({ c.getRadius(), c.getRadius()});
        c.setFillColor(sf::Color::Yellow);
        c.setOutlineColor(sf::Color::Red);
        c.setOutlineThickness(8.0f);

        target.draw(c, info);

        const float margin = 4.0f;
        const float barSize = 32.0f;
        const float barLength = size.x - barSize;

        info.transform.translate({0.0f, size.y - barSize * 2 });
        sf::RectangleShape progress = sf::RectangleShape(sf::Vector2f(barLength, barSize));
        progress.setPosition(sf::Vector2f(-barLength / 2.0f, -size.y / 2.0f + barSize / 2.0f));

        progress.setFillColor(sf::Color::Blue);
        target.draw(progress, info);
        progress.setSize(sf::Vector2f(barLength * m_Percentage / 100.0f - margin * 2.0f, progress.getGlobalBounds().size.y - margin * 2.0f));
        progress.setPosition(progress.getPosition() + sf::Vector2f(margin, margin));
        progress.setFillColor(sf::Color::Green);
        target.draw(progress, info);
	}

}