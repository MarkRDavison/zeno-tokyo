#include <tokyo/Driller/Views/ShuttleView.hpp>

namespace drl
{

	ShuttleView::ShuttleView(
		const ShuttleData& _shuttleData,
		const IShuttlePrototypeService& _shuttlePrototypeService,
		const tokyo::TextureManager& _textureManager
	) :
		m_ShuttleData(_shuttleData),
		m_ShuttlePrototypeService(_shuttlePrototypeService),
		m_TextureManager(_textureManager)
	{

	}

	void ShuttleView::update(float _delta)
	{

	}
	void ShuttleView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
	{
		_states.texture = &m_TextureManager.getTexture(Constants::TileSpriteSheetTextureName);
		sf::Vector2f textureSize(_states.texture->getSize());

		sf::VertexArray shuttles(sf::PrimitiveType::Triangles);

		for (const auto& s : m_ShuttleData.shuttles)
		{
			const auto& prototype = m_ShuttlePrototypeService.getPrototype(s.prototypeId);

			const sf::Vector2f offset(-(float)((prototype.size.x - 1.0f) / 2.0f), (float)prototype.size.y);

			for (int y = 0; y <= prototype.size.y - 1; ++y)
			{
				for (int x = 0; x <= prototype.size.x - 1; ++x)
				{
					const auto textureCoords = sf::Vector2u(prototype.texture) + sf::Vector2u(x, y);
					appendCell(shuttles, textureCoords, { x,-y }, textureSize, offset +s.position);
				}
			}
		}

		_target.draw(shuttles, _states);
	}

}