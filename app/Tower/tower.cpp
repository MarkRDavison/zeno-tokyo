#include <SFML/Graphics.hpp>
#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/InputActionManager.hpp>

// https://www.reddit.com/r/gamedesign/s/2KBao2605y

int main()
{
    tokyo::Log::Info("Info\n");
    tokyo::Log::Warning("Warning\n");
    tokyo::Log::Error("Error\n");
    tokyo::Log::Assert(true, "Assert pass\n");

    auto window = sf::RenderWindow(sf::VideoMode({ 1280, 720 }), "CMake SFML Project");
    window.setFramerateLimit(144);

    tokyo::InputManager inputManager(window);
    tokyo::InputActionManager inputActionManager(inputManager);
    
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
            //if (inputActionManager.IsActionInvoked("LCLICK"))
            //{
            //    std::cout << "LCLICK Invoked!" << std::endl;
            //}
            //
            //if (inputActionManager.IsActionInvoked("SPACE"))
            //{
            //    std::cout << "SPACE Invoked!" << std::endl;
            //}
        }

        inputActionManager.updateCachedInputs();

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