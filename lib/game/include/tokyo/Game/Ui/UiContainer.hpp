#pragma once

#include <tokyo/Game/Ui/UiComponent.hpp>

namespace tokyo
{
	class UiContainer : public UiComponent
	{
	public:
		UiContainer();

		void init() override;
		void updateSelf() override;
		bool isMouseOver() override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}