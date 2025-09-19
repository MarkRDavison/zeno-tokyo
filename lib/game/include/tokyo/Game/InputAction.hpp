#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>

namespace tokyo
{
	struct InputAction
	{
		enum class InputActivationType
		{
			KeyPress,
			KeyHold,
			MouseButtonPress,
			MouseButtonHold,
			None
		};


		InputActivationType primaryActivationType{ InputActivationType::None };
		sf::Keyboard::Key primaryKey{ sf::Keyboard::Key::Unknown };
		sf::Mouse::Button primaryButton{ (sf::Mouse::Button)-1};

		InputActivationType secondaryActivationType{ InputActivationType::None };
		sf::Keyboard::Key secondaryKey{ sf::Keyboard::Key::Unknown };
		sf::Mouse::Button secondaryButton{ (sf::Mouse::Button)-1 };

		// If secondary required to activate requires both otherwise requires either
		bool secondaryRequired{ false };
		bool allowRepeat{ false };

		bool modifierControl{ false };
		bool modifierAlt{ false };
		bool modifierShift{ false };
	};
}