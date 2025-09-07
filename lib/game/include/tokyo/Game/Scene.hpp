#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace tokyo
{
	class Scene : public sf::Drawable
	{
	public:
		virtual void Update(float delta) = 0;
		virtual void Start() {}
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	protected:
		bool started{ false };
		bool active{ true };
	};

}