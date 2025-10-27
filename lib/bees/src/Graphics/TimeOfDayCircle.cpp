#include <tokyo/Bees/Graphics/TimeOfDayCircle.hpp>
#include <SFML/Graphics.hpp>

namespace bee
{

	TimeOfDayCircle::TimeOfDayCircle(
		float size,
		const BeeGameTime& gameTime
	) :
		_size(size),
		_gameTime(gameTime)
	{

	}

	void TimeOfDayCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		const int points = 60;

		const auto PI_2 = 3.14159265f * 2.0f;

		auto arcAngle = PI_2 / static_cast<float>(points);

		sf::VertexArray c(sf::PrimitiveType::Triangles);

		const auto nightThreshold = (int)(points * _gameTime.getNightThreshold());

		for (int i = 0; i < points; ++i)
		{
			auto col = i < nightThreshold ? sf::Color::Yellow : sf::Color::Blue;

			const auto angle = arcAngle * i + PI_2 * _gameTime.getNormalisedTime();

			c.append(sf::Vertex(sf::Vector2f(), col));
			c.append(sf::Vertex(sf::Vector2f(_size * std::cos(angle), _size * std::sin(angle)), col));
			c.append(sf::Vertex(sf::Vector2f(_size * std::cos(angle + arcAngle), _size * std::sin(angle + arcAngle)), col));
		}

		target.draw(c, states);
	}
}