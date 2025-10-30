#include <tokyo/Game/Ui/UiContainer.hpp>
#include <SFML/Graphics.hpp>

namespace tokyo
{
	UiContainer::UiContainer()
	{
		forceInitialisation(0.0f, 0.0f, 1.0f, 1.0f);
	}


	void UiContainer::init()
	{

	}
	void UiContainer::updateSelf()
	{

	}
	bool UiContainer::isMouseOver()
	{
		for (auto c : getChildren())
		{
			if (c->isMouseOver())
			{
				return true;
			}
		}

		return false;
	}

	void UiContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		auto x = this->getAbsX();
		auto y = this->getAbsY();
		auto w = this->getAbsWidth();
		auto h = this->getAbsHeight();
		sf::RectangleShape r(sf::Vector2f(w, h));
		r.setPosition(sf::Vector2f(x, y));
		r.setFillColor(sf::Color::Green);
		target.draw(r, states);
	}
}