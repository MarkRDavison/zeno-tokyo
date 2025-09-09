#pragma once

#include <SFML/Graphics.hpp>

namespace drl
{
	class View : public sf::Drawable
	{
	public:
		virtual ~View();
		virtual void update(float _delta) = 0;
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const = 0;

		void appendCell(
			sf::VertexArray& _vertex,
			sf::Vector2u _textureTileCoordinates,
			sf::Vector2i _tileCoordinates,
			sf::Vector2f _textureSize,
			sf::Vector2f _offset = sf::Vector2f()
		) const;
	};

	inline View::~View(void) = default;
}