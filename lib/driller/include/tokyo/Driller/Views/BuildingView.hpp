#pragma once

#include <tokyo/Driller/Entities/Data/BuildingData.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Driller/Services/Building/BuildingPrototypeService.hpp>
#include <tokyo/Driller/Views/View.hpp>

namespace drl
{

	class BuildingView : public View
	{
	public:
		BuildingView(
			const BuildingData& _buildingData,
			const IBuildingPrototypeService& _buildingPrototypeService,
			const tokyo::TextureManager& _textureManager
		);
		~BuildingView(void) override = default;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:
		const BuildingData& m_BuildingData;
		const IBuildingPrototypeService& m_BuildingPrototypeService;
		const tokyo::TextureManager& m_TextureManager;
	};

}