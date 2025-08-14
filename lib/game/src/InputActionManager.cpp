#include <tokyo/Game/InputActionManager.hpp>

namespace tokyo
{
	void InputActionManager::UpdateInputCache()
	{
		for (auto& [key, down] : _cachedKeys)
		{
			down = sf::Keyboard::isKeyPressed(key);
		}

		for (auto& [button, down] : _cachedButtons)
		{
			down = sf::Mouse::isButtonPressed(button);
		}
	}

	void InputActionManager::RegisterInputActionType(const InputActionType& action)
	{
		_actions[action.name] = action;

		if (action.actionType == ActionType::KEY)
		{
			_cachedKeys[action.key] = false;
		}

		if (action.actionType == ActionType::MOUSE_BUTTON)
		{
			_cachedButtons[action.mouseButton] = false;
		}
	}

	bool InputActionManager::IsActionInvoked(const std::string& name) const
	{
		const auto actionIter = _actions.find(name);

		if (actionIter != _actions.end())
		{
			const auto& action = (*actionIter).second;

			switch (action.actionType)
			{
				case ActionType::KEY:
				{
					return sf::Keyboard::isKeyPressed(action.key) && !_cachedKeys.at(action.key);
				}
				break;
				case ActionType::MOUSE_BUTTON:
				{
					return sf::Mouse::isButtonPressed(action.mouseButton) && !_cachedButtons.at(action.mouseButton);
				}
				break;
			}
		}

		return false;
	}

}