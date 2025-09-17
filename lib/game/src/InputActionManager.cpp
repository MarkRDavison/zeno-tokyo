#include <tokyo/Game/InputActionManager.hpp>

namespace tokyo
{

	InputActionManager::InputActionManager(IInputManager& _inputManager) :
		m_InputManager(_inputManager)
	{

	}

	void InputActionManager::registerAction(const std::string& _key, const InputAction& _action)
	{
		registeredActions[_key] = _action;
		if (_action.primaryActivationType == InputAction::InputActivationType::KeyHold ||
			_action.primaryActivationType == InputAction::InputActivationType::KeyPress)
		{
			cachedKeys.emplace(_action.primaryKey, false);
		}
		else if (
			_action.primaryActivationType == InputAction::InputActivationType::MouseButtonHold ||
			_action.primaryActivationType == InputAction::InputActivationType::MouseButtonPress)
		{
			cachedButtons.emplace(_action.primaryButton, false);
		}

		if (_action.secondaryActivationType == InputAction::InputActivationType::KeyHold ||
			_action.secondaryActivationType == InputAction::InputActivationType::KeyPress)
		{
			cachedKeys.emplace(_action.secondaryKey, false);
		}
		else if (
			_action.secondaryActivationType == InputAction::InputActivationType::MouseButtonHold ||
			_action.secondaryActivationType == InputAction::InputActivationType::MouseButtonPress)
		{
			cachedButtons.emplace(_action.secondaryButton, false);
		}
	}
	void InputActionManager::updateCachedInputs()
	{
		for (auto& [button, value] : cachedButtons)
		{
			value = m_InputManager.isButtonDown(button);
		}
		for (auto& [key, value] : cachedKeys)
		{
			value = m_InputManager.isKeyDown(key);
		}
	}

	bool InputActionManager::isActionInvoked(const std::string& _key) const
	{
		const auto& iter = registeredActions.find(_key);
		if (iter == registeredActions.end())
		{
			return false;
		}
		return isActionInvoked((*iter).second);
	}

	bool InputActionManager::isActionInvoked(const InputAction& _action) const
	{
		if (_action.primaryActivationType == InputAction::InputActivationType::KeyHold ||
			_action.primaryActivationType == InputAction::InputActivationType::KeyPress)
		{
			if (m_InputManager.isKeyDown(_action.primaryKey) &&
				(!_action.modifierControl || m_InputManager.isKeyDown(sf::Keyboard::Key::LControl) || m_InputManager.isKeyDown(sf::Keyboard::Key::RControl)) &&
				(!_action.modifierShift || m_InputManager.isKeyDown(sf::Keyboard::Key::LShift) || m_InputManager.isKeyDown(sf::Keyboard::Key::RShift)) &&
				(!_action.modifierAlt || m_InputManager.isKeyDown(sf::Keyboard::Key::LAlt) || m_InputManager.isKeyDown(sf::Keyboard::Key::RAlt)))
			{
				if (_action.primaryActivationType == InputAction::InputActivationType::KeyPress)
				{
					return !cachedKeys.at(_action.primaryKey);
				}
				return true;
			}
		}
		if (_action.secondaryActivationType == InputAction::InputActivationType::KeyHold ||
			_action.secondaryActivationType == InputAction::InputActivationType::KeyPress)
		{
			if (m_InputManager.isKeyDown(_action.secondaryKey) &&
				(!_action.modifierControl || m_InputManager.isKeyDown(sf::Keyboard::Key::LControl) || m_InputManager.isKeyDown(sf::Keyboard::Key::RControl)) &&
				(!_action.modifierShift || m_InputManager.isKeyDown(sf::Keyboard::Key::LShift) || m_InputManager.isKeyDown(sf::Keyboard::Key::RShift)) &&
				(!_action.modifierAlt || m_InputManager.isKeyDown(sf::Keyboard::Key::LAlt) || m_InputManager.isKeyDown(sf::Keyboard::Key::RAlt)))
			{
				if (_action.secondaryActivationType == InputAction::InputActivationType::KeyPress)
				{
					return !cachedKeys.at(_action.secondaryKey);
				}
				return true;
			}
		}

		if (_action.primaryActivationType == InputAction::InputActivationType::MouseButtonHold ||
			_action.primaryActivationType == InputAction::InputActivationType::MouseButtonPress)
		{
			if (m_InputManager.isButtonDown(_action.primaryButton) &&
				(!_action.modifierControl || m_InputManager.isKeyDown(sf::Keyboard::Key::LControl) || m_InputManager.isKeyDown(sf::Keyboard::Key::RControl)) &&
				(!_action.modifierShift || m_InputManager.isKeyDown(sf::Keyboard::Key::LShift) || m_InputManager.isKeyDown(sf::Keyboard::Key::RShift)) &&
				(!_action.modifierAlt || m_InputManager.isKeyDown(sf::Keyboard::Key::LAlt) || m_InputManager.isKeyDown(sf::Keyboard::Key::RAlt)))
			{
				if (_action.primaryActivationType == InputAction::InputActivationType::MouseButtonPress)
				{
					return !cachedButtons.at(_action.primaryButton);
				}
				return true;
			}
		}
		if (_action.secondaryActivationType == InputAction::InputActivationType::MouseButtonHold ||
			_action.secondaryActivationType == InputAction::InputActivationType::MouseButtonPress)
		{
			if (m_InputManager.isButtonDown(_action.secondaryButton) &&
				(!_action.modifierControl || m_InputManager.isKeyDown(sf::Keyboard::Key::LControl) || m_InputManager.isKeyDown(sf::Keyboard::Key::RControl)) &&
				(!_action.modifierShift || m_InputManager.isKeyDown(sf::Keyboard::Key::LShift) || m_InputManager.isKeyDown(sf::Keyboard::Key::RShift)) &&
				(!_action.modifierAlt || m_InputManager.isKeyDown(sf::Keyboard::Key::LAlt) || m_InputManager.isKeyDown(sf::Keyboard::Key::RAlt)))
			{
				if (_action.secondaryActivationType == InputAction::InputActivationType::MouseButtonPress)
				{
					return !cachedButtons.at(_action.secondaryButton);
				}
				return true;
			}
		}

		return false;
	}
	sf::Vector2i InputActionManager::getMousePosition() const
	{
		return m_InputManager.getMousePosition();
	}
	sf::Vector2u InputActionManager::getWindowSize() const
	{
		return m_InputManager.getWindowSize();
	}
	bool InputActionManager::isKeyDown(sf::Keyboard::Key _key)
	{
		return m_InputManager.isKeyDown(_key);
	}
	bool InputActionManager::isButtonDown(sf::Mouse::Button _button)
	{
		return m_InputManager.isButtonDown(_button);
	}
}