#include <tokyo/Driller/Views/BuildingView.hpp>

namespace drl
{


	BuildingView::BuildingView(
		const BuildingData& _buildingData,
		const IBuildingPrototypeService& _buildingPrototypeService,
		const tokyo::TextureManager& _textureManager
	) :
		m_BuildingData(_buildingData),
		m_BuildingPrototypeService(_buildingPrototypeService),
		m_TextureManager(_textureManager)
	{

	}

	void BuildingView::update(float)
	{

	}
	void BuildingView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
	{
		_states.texture = &m_TextureManager.getTexture(Constants::TileSpriteSheetTextureName);
		sf::Vector2f textureSize(_states.texture->getSize());

		sf::VertexArray buildings(sf::PrimitiveType::Triangles);

		for (const auto& b : m_BuildingData.buildings)
		{
			const auto& prototype = m_BuildingPrototypeService.getPrototype(b.prototypeId);

			for (int y = 0; y <= prototype.size.y - 1; ++y)
			{
				for (int x = 0; x <= prototype.size.x - 1; ++x)
				{
					const auto coords = sf::Vector2i(b.coordinates) + sf::Vector2i(x, y);
					const auto textureCoords = sf::Vector2u(prototype.texture) + sf::Vector2u(x, y);
					appendCell(buildings, textureCoords, {coords.x, -coords.y}, textureSize);
				}
			}
		}

		_target.draw(buildings, _states);
	}

}