#pragma once

#include <tokyo/Driller/Entities/Data/ShuttleData.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttlePrototypeService.hpp>
#include <tokyo/Driller/Views/View.hpp>

namespace drl
{

	class ShuttleView : public View
	{
	public:
		ShuttleView(
			const ShuttleData& _shuttleData,
			const IShuttlePrototypeService& _shuttlePrototypeService,
			const tokyo::TextureManager& _textureManager
		);
		~ShuttleView(void) override = default;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:
		const ShuttleData& m_ShuttleData;
		const IShuttlePrototypeService& m_ShuttlePrototypeService;
		const tokyo::TextureManager& m_TextureManager;
	};

}