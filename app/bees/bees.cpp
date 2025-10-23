#include <SFML/Graphics.hpp>
#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/InputActionManager.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1280, 720 }), "Tokyo Bees");
    window.setVerticalSyncEnabled(true);

    tokyo::InputManager inputManager(window);
    tokyo::InputActionManager inputActionManager(inputManager);

    inputActionManager.registerAction("LCLICK",
        {
            .primaryActivationType = tokyo::InputAction::InputActivationType::MouseButtonPress,
            .primaryButton = sf::Mouse::Button::Left
        });

    inputActionManager.registerAction("SPACE",
        {
            .primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress,
            .primaryKey = sf::Keyboard::Key::Space
        });

    const std::string resourceRoot = "F:/Workspace/Github/zeno-tokyo/app/bees/data";

    auto running = true;

    while (running)
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                running = false;
            }
        }

        // update
        {
            if (inputActionManager.isActionInvoked("SPACE"))
            {
                tokyo::Log::Info("SPACE!!!\n");
            }
            if (inputActionManager.isActionInvoked("LCLICK"))
            {
                tokyo::Log::Info("LCLICK!!!\n");
            }
        }

        inputActionManager.updateCachedInputs();

        window.clear(sf::Color::Cyan);

        // render
        {

        }

        window.display();
    }

    window.close();
}