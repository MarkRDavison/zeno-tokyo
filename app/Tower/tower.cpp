#include <SFML/Graphics.hpp>
#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/InputActionManager.hpp>

int main()
{
    tokyo::Log::Info("Info\n");
    tokyo::Log::Warning("Warning\n");
    tokyo::Log::Error("Error\n");
    tokyo::Log::Assert(true, "Assert pass\n");

    auto window = sf::RenderWindow(sf::VideoMode({ 1280, 720 }), "CMake SFML Project");
    window.setFramerateLimit(144);

    tokyo::InputActionManager inputActionManager;
    
    inputActionManager.RegisterInputActionType(tokyo::InputActionType
    { 
        .name = "LCLICK", 
        .mouseButton = sf::Mouse::Button::Left, 
        .actionType = tokyo::ActionType::MOUSE_BUTTON 
    });
    
    inputActionManager.RegisterInputActionType(tokyo::InputActionType
    { 
        .name = "SPACE", 
        .key = sf::Keyboard::Key::Space,
        .actionType = tokyo::ActionType::KEY 
    });

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
            if (inputActionManager.IsActionInvoked("LCLICK"))
            {
                std::cout << "LCLICK Invoked!" << std::endl;
            }

            if (inputActionManager.IsActionInvoked("SPACE"))
            {
                std::cout << "SPACE Invoked!" << std::endl;
            }
        }

        inputActionManager.UpdateInputCache();

        window.clear(sf::Color::Cyan);

        // render
        {
            sf::CircleShape c(64.0f);
            c.setFillColor(sf::Color::Magenta);
            c.setOrigin({ 32.0f, 32.0f });

            auto state = sf::RenderStates::Default;
            state.transform.translate(sf::Vector2f(window.getSize()) / 2.0f);

            window.draw(c, state);
        }

        window.display();
    }
    window.close();
}