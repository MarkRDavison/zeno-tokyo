#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace sf
{
	class Window;
}

namespace tokyo
{
	class IInputManager
	{
	public:
		virtual ~IInputManager() = 0;
		virtual sf::Vector2i getMousePosition() const = 0;
		virtual sf::Vector2u getWindowSize() const = 0;
		virtual bool isKeyDown(sf::Keyboard::Key _key) const = 0;
		virtual bool isButtonDown(sf::Mouse::Button _button) const = 0;

	};

	class InputManager : public IInputManager
	{
	public:
		InputManager(const sf::Window& _window);
		~InputManager() override;

		sf::Vector2i getMousePosition() const override;
		sf::Vector2u getWindowSize() const override;
		bool isKeyDown(sf::Keyboard::Key _key) const override;
		bool isButtonDown(sf::Mouse::Button _button) const override;


	private:
		const sf::Window& m_Window;
	};

	inline IInputManager::~IInputManager() = default;

}