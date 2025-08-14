#pragma once

#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Game/InputActionType.hpp>

#include <string>
#include <unordered_map>

namespace tokyo
{

	class InputActionManager : NonCopyable
	{
	public:
		InputActionManager() = default;
		void UpdateInputCache();
		void RegisterInputActionType(const InputActionType& action);
		bool IsActionInvoked(const std::string& name) const;

	private:
		std::unordered_map<std::string, InputActionType> _actions;
		std::unordered_map<sf::Keyboard::Key, bool> _cachedKeys;
		std::unordered_map<sf::Mouse::Button, bool> _cachedButtons;
	};
}