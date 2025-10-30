#pragma once

#include <tokyo/Game/Ui/UiComponent.hpp>

namespace tokyo
{

	class UiPanel : public UiComponent
	{
	public:
		void init() override;

		void updateSelf(void) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:



	};

}