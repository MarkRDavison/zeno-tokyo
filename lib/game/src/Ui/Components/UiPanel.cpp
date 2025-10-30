#include <tokyo/Game/Ui/Components/UiPanel.hpp>
#include <SFML/Graphics.hpp>

namespace tokyo
{
	void UiPanel::init()
	{
	}

	void UiPanel::updateSelf(void)
	{
	}

	void UiPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sf::RectangleShape r(sf::Vector2f(this->getAbsX(), this->getAbsY()));
		r.setPosition(sf::Vector2f(this->getAbsX(), this->getAbsY()));
		r.setFillColor(sf::Color::Green);
		target.draw(r, states);
	}
}