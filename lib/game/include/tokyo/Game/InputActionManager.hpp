#pragma once

#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Game/InputAction.hpp>
#include <tokyo/Game/InputManager.hpp>

#include <string>
#include <unordered_map>

namespace tokyo
{

	class IInputActionManager : NonCopyable
	{
	public:
		virtual ~IInputActionManager() = 0;

		virtual void registerAction(const std::string& _key, const InputAction& _action) = 0;
		virtual void updateCachedInputs() = 0;

		virtual bool isActionInvoked(const std::string& _key) const = 0;
	};

	class InputActionManager : public IInputActionManager
	{
	public:
		InputActionManager(IInputManager& _inputManager);
		~InputActionManager() override = default;

		void registerAction(const std::string& _key, const InputAction& _action) override;
		void updateCachedInputs() override;

		bool isActionInvoked(const std::string& _key) const override;
		bool isActionInvoked(const InputAction& _action) const;

	private:
		IInputManager& m_InputManager;
		std::unordered_map<std::string, InputAction> registeredActions;
		std::unordered_map<sf::Mouse::Button, bool> cachedButtons;
		std::unordered_map<sf::Keyboard::Key, bool> cachedKeys;
	};

	inline IInputActionManager::~IInputActionManager() = default;
}