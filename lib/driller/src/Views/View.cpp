#include <tokyo/Driller/Views/View.hpp>

namespace drl
{
	void View::appendCell(
		sf::VertexArray& _vertex,
		sf::Vector2u _textureTileCoordinates,
		sf::Vector2i _tileCoordinates,
		sf::Vector2f _textureSize,
		sf::Vector2f _offset
	) const
	{
		constexpr float EPSILON{ 0.0004f };
		constexpr float TEXTURE_CELL_SIZE{ 64.0f };

		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y) + 0.0f) +
			_offset,
			sf::Color::White,
			sf::Vector2f(
				_textureTileCoordinates.x + 0,
				_textureTileCoordinates.y + 0
			) * TEXTURE_CELL_SIZE +
			sf::Vector2f(+EPSILON, -EPSILON))
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) + 0.5f,
				static_cast<float>(_tileCoordinates.y) + 0.0f) +
			_offset,
			sf::Color::White,
			sf::Vector2f(
				_textureTileCoordinates.x + 1,
				_textureTileCoordinates.y + 0
			) * TEXTURE_CELL_SIZE +
			sf::Vector2f(-EPSILON, -EPSILON))
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) + 0.5f,
				static_cast<float>(_tileCoordinates.y) - 1.0f) +
			_offset,
			sf::Color::White,
			sf::Vector2f(
				_textureTileCoordinates.x + 1,
				_textureTileCoordinates.y + 1
			) * TEXTURE_CELL_SIZE +
			sf::Vector2f(-EPSILON, +EPSILON))
		);

		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y) + 0.0f) +
			_offset,
			sf::Color::White,
			sf::Vector2f(
				_textureTileCoordinates.x + 0,
				_textureTileCoordinates.y + 0
			) * TEXTURE_CELL_SIZE +
			sf::Vector2f(+EPSILON, -EPSILON))
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) + 0.5f,
				static_cast<float>(_tileCoordinates.y) - 1.0f) +
			_offset,
			sf::Color::White,
			sf::Vector2f(
				_textureTileCoordinates.x + 1,
				_textureTileCoordinates.y + 1
			) * TEXTURE_CELL_SIZE +
			sf::Vector2f(-EPSILON, +EPSILON))
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y) - 1.0f) +
			_offset,
			sf::Color::White,
			sf::Vector2f(
				_textureTileCoordinates.x + 0,
				_textureTileCoordinates.y + 1
			) * TEXTURE_CELL_SIZE +
			sf::Vector2f(+EPSILON, +EPSILON))
		);
	}
}