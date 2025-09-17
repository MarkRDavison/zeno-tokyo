#include <tokyo/Game/InputManager.hpp>

#include <SFML/Window/Window.hpp>

namespace tokyo
{

	InputManager::InputManager(const sf::Window& _window) :
		m_Window(_window)
	{

	}
	InputManager::~InputManager()
	{

	}

	sf::Vector2i InputManager::getMousePosition() const
	{
		return sf::Mouse::getPosition(m_Window);
	}

	sf::Vector2u InputManager::getWindowSize() const
	{
		return m_Window.getSize();
	}

	bool InputManager::isKeyDown(sf::Keyboard::Key _key) const
	{
		return sf::Keyboard::isKeyPressed(_key);
	}

	bool InputManager::isButtonDown(sf::Mouse::Button _button) const
	{
		return sf::Mouse::isButtonPressed(_button);
	}

}