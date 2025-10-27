#pragma once

#include <tokyo/Bees/World/BeeGameTime.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace bee
{
	class TimeOfDayCircle : public sf::Drawable
	{
	public:
		TimeOfDayCircle(float size, const BeeGameTime& gameTime);
	private:
		const float _size;
		const BeeGameTime& _gameTime;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}