#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>

namespace tokyo
{
	enum class ActionType
	{
		KEY,
		MOUSE_BUTTON,

		NONE
	};

	struct InputActionType
	{
		std::string name{};
		sf::Keyboard::Key key{ sf::Keyboard::Key::Unknown };
		sf::Mouse::Button mouseButton{ sf::Mouse::Button(5)};
		ActionType actionType{ ActionType::NONE };
	};
}