#pragma once

#include <tokyo/Driller/Entities/Data/TerrainData.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Driller/Views/View.hpp>

namespace drl
{

	class TerrainView : public View
	{
	public:
		TerrainView(
			const TerrainData& _terrainData,
			const tokyo::TextureManager& _textureManager
		);
		~TerrainView(void) override = default;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:

		const TerrainData& m_TerrainData;
		const tokyo::TextureManager& m_TextureManager;
	};

}