#include <SFML/Graphics.hpp>
#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Game/Resource/TextureService.hpp>

int main()
{
    tokyo::Log::Info("http://sokobano.de/wiki/index.php?title=How_to_play_Sokoban\n");
    tokyo::Log::Info("https://www.reddit.com/r/gamedesign/s/2KBao2605y\n");
    tokyo::Log::Info("https://github.com/eranpeer/FakeIt\n");

    auto window = sf::RenderWindow(sf::VideoMode({ 1280, 720 }), "Tokyo Sokoban");
    window.setVerticalSyncEnabled(true);

    tokyo::InputManager inputManager(window);
    tokyo::InputActionManager inputActionManager(inputManager);
    tokyo::TextureService textureService;
    
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

    const std::string resourceRoot = "F:/Workspace/Github/zeno-tokyo/app/Sokoban/data";

    textureService.loadTexture("spritesheet", resourceRoot + "/spritesheets/sokoban_spritesheet@2.png");

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