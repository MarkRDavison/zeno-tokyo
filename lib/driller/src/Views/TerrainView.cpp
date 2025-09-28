#include <tokyo/Driller/Views/TerrainView.hpp>
#include <tokyo/Driller/Constants.hpp>

namespace drl
{

	TerrainView::TerrainView(
		const TerrainData& _terrainData,
		const tokyo::TextureManager& _textureManager
	) :
		m_TerrainData(_terrainData),
		m_TextureManager(_textureManager)
	{

	}

	void TerrainView::update(float)
	{

	}
	void TerrainView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
	{
		const sf::Vector2u DefaultTerrain{ 0, 0 };
		const sf::Vector2u DugOutTerrain{ 1, 0 };
		const sf::Vector2u LadderTerrain{ 0, 1 };
		const sf::Vector2u DrillTerrain{ 0, 2 };

		_states.texture = &m_TextureManager.getTexture(Constants::TileSpriteSheetTextureName);
		sf::Vector2f textureSize(_states.texture->getSize());

		sf::VertexArray terrainLeft(sf::PrimitiveType::Triangles);
		sf::VertexArray terrainCenter(sf::PrimitiveType::Triangles);
		sf::VertexArray terrainRight(sf::PrimitiveType::Triangles);
		{
			for (int i = 0; i < static_cast<int>(m_TerrainData.rows.size()); ++i) 
			{
				const TerrainRow& row = m_TerrainData.rows[i];

				for (int j = 1; j <= static_cast<int>(row.leftTiles.size()); ++j) 
				{
					appendCell(terrainLeft, row.leftTiles[j - 1].dugOut ? DugOutTerrain : DefaultTerrain, { -j, -i }, textureSize);
				}

				for (int k = 1; k <= static_cast<int>(row.rightTiles.size()); ++k) 
				{
					appendCell(terrainRight, row.rightTiles[k - 1].dugOut ? DugOutTerrain : DefaultTerrain, { +k, -i }, textureSize);
				}
			}

			int shaftI = 0;

			for (; shaftI <= m_TerrainData.shaftLevel; ++shaftI) 
			{
				appendCell(terrainCenter, LadderTerrain, { 0, -shaftI }, textureSize);
			}

			appendCell(terrainCenter, DrillTerrain, sf::Vector2i(0, -shaftI), textureSize);
		}


		if (terrainLeft.getVertexCount() > 0) 
		{
			_target.draw(terrainLeft, _states);
		}

		if (terrainCenter.getVertexCount() > 0)
		{
			_target.draw(terrainCenter, _states);
		}

		if (terrainRight.getVertexCount() > 0)
		{
			_target.draw(terrainRight, _states);
		}
	}
}