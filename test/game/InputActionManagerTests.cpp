#include <catch2/catch_test_macros.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <fakeit.hpp>

namespace tokyo
{
	namespace test
	{

		TEST_CASE("non registered action is not invoked", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());
			InputAction ac;
			REQUIRE_FALSE(actionManager.isActionInvoked(ac));
		}

		TEST_CASE("registered button down action is invoked and delegates to input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			const std::string actionName = "ACTION_NAME";

			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::KeyHold;
			action.primaryKey = sf::Keyboard::Key::Space;

			fakeit::When(Method(inputManager, isKeyDown)).AlwaysReturn(true);

			actionManager.registerAction(actionName, action);

			REQUIRE(actionManager.isActionInvoked(actionName));

			fakeit::Verify(Method(inputManager, isKeyDown).Using(action.primaryKey));
		}

		TEST_CASE("updateCachedInputs invokes the underlying input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			fakeit::When(Method(inputManager, isButtonDown)).AlwaysReturn(true);
			fakeit::When(Method(inputManager, isKeyDown)).AlwaysReturn(true);

			const sf::Keyboard::Key key = sf::Keyboard::Key::Space;
			const sf::Mouse::Button button = sf::Mouse::Button::Left;

			const std::string actionName = "ACTION_NAME";
			InputAction action{};

			action.primaryActivationType = InputAction::InputActivationType::KeyHold;
			action.primaryKey = sf::Keyboard::Key::Space;
			actionManager.registerAction(actionName, action);

			action.primaryActivationType = InputAction::InputActivationType::MouseButtonHold;
			action.primaryButton = sf::Mouse::Button::Left;
			actionManager.registerAction(actionName, action);

			REQUIRE_NOTHROW(actionManager.updateCachedInputs());

			fakeit::Verify(Method(inputManager, isButtonDown).Using(button));
			fakeit::Verify(Method(inputManager, isKeyDown).Using(key));
		}

		TEST_CASE("registered key down action is invoked and delegates to input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			const std::string actionName = "ACTION_NAME";

			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::MouseButtonHold;
			action.primaryButton = sf::Mouse::Button::Left;

			fakeit::When(Method(inputManager, isButtonDown)).AlwaysReturn(true);

			actionManager.registerAction(actionName, action);

			REQUIRE(actionManager.isActionInvoked(action));

			fakeit::Verify(Method(inputManager, isButtonDown).Using(action.primaryButton));
		}

		TEST_CASE("action with no activation type returns false without querying input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			InputAction action{};

			REQUIRE_FALSE(actionManager.isActionInvoked(action));
		}

		TEST_CASE("action with simple key down primary only returns based on underlying input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::KeyHold;
			action.primaryKey = sf::Keyboard::Key::Space;

			fakeit::When(Method(inputManager, isKeyDown)).AlwaysReturn(true);

			REQUIRE(actionManager.isActionInvoked(action));

			fakeit::Verify(Method(inputManager, isKeyDown).Using(action.primaryKey));
		}

		TEST_CASE("action with simple button down primary only returns based on underlying input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::MouseButtonHold;
			action.primaryButton = sf::Mouse::Button::Left;

			fakeit::When(Method(inputManager, isButtonDown)).AlwaysReturn(true);

			REQUIRE(actionManager.isActionInvoked(action));

			fakeit::Verify(Method(inputManager, isButtonDown).Using(action.primaryButton));
		}

		TEST_CASE("action with primary key press using cached inputs works as expected", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			fakeit::When(Method(inputManager, isKeyDown)).AlwaysReturn(true);

			const sf::Keyboard::Key key = sf::Keyboard::Key::Space;

			const std::string actionName = "ACTION_NAME";
			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::KeyPress;
			action.primaryKey = key;

			actionManager.registerAction(actionName, action);

			REQUIRE(actionManager.isActionInvoked(actionName));

			actionManager.updateCachedInputs();

			REQUIRE_FALSE(actionManager.isActionInvoked(actionName));

			fakeit::Verify(Method(inputManager, isKeyDown).Using(key));
		}


		TEST_CASE("action with primary button press using cached inputs works as expected", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			fakeit::When(Method(inputManager, isButtonDown)).AlwaysReturn(true);

			const sf::Mouse::Button button = sf::Mouse::Button::Left;

			const std::string actionName = "ACTION_NAME";
			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::MouseButtonPress;
			action.primaryButton = button;

			actionManager.registerAction(actionName, action);

			REQUIRE(actionManager.isActionInvoked(actionName));

			actionManager.updateCachedInputs();

			REQUIRE_FALSE(actionManager.isActionInvoked(actionName));

			fakeit::Verify(Method(inputManager, isButtonDown).Using(button));
		}

		TEST_CASE("action with primary button press using cached inputs and modifier key works as expected", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			fakeit::When(Method(inputManager, isButtonDown)).AlwaysReturn(true);

			const sf::Mouse::Button button = sf::Mouse::Button::Left;
			fakeit::When(Method(inputManager, isKeyDown)).AlwaysDo([](const sf::Keyboard::Key& _key) -> bool
				{
					return _key == sf::Keyboard::Key::RControl;
				});

			const std::string actionName = "ACTION_NAME";
			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::MouseButtonPress;
			action.primaryButton = button;
			action.modifierControl = true;

			actionManager.registerAction(actionName, action);

			REQUIRE(actionManager.isActionInvoked(actionName));

			actionManager.updateCachedInputs();

			REQUIRE_FALSE(actionManager.isActionInvoked(actionName));

			fakeit::Verify(Method(inputManager, isButtonDown).Using(button));
		}

		TEST_CASE("action with simple key down secondary only returns based on underlying input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::KeyHold;
			action.primaryKey = sf::Keyboard::Key::Space;
			action.secondaryActivationType = InputAction::InputActivationType::KeyHold;
			action.secondaryKey = sf::Keyboard::Key::Backspace;

			fakeit::When(Method(inputManager, isKeyDown)).AlwaysDo([&](const sf::Keyboard::Key& _key) -> bool
				{
					return _key == action.secondaryKey;
				});

			REQUIRE(actionManager.isActionInvoked(action));

			fakeit::Verify(Method(inputManager, isKeyDown).Using(action.primaryKey));
			fakeit::Verify(Method(inputManager, isKeyDown).Using(action.secondaryKey));
		}

		TEST_CASE("action with simple button down secondary only returns based on underlying input manager", "[InputActionManager]")
		{
			fakeit::Mock<IInputManager> inputManager;
			InputActionManager actionManager(inputManager.get());

			InputAction action{};
			action.primaryActivationType = InputAction::InputActivationType::MouseButtonHold;
			action.primaryButton = sf::Mouse::Button::Left;
			action.secondaryActivationType = InputAction::InputActivationType::MouseButtonHold;
			action.secondaryButton = sf::Mouse::Button::Right;

			fakeit::When(Method(inputManager, isButtonDown)).AlwaysDo([&](const sf::Mouse::Button& _button)->bool
				{
					return _button == action.secondaryButton;
				});

			REQUIRE(actionManager.isActionInvoked(action));

			fakeit::Verify(Method(inputManager, isButtonDown).Using(action.primaryButton));
			fakeit::Verify(Method(inputManager, isButtonDown).Using(action.secondaryButton));
		}

	}
}