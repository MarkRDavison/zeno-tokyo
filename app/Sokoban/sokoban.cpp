#include <SFML/Graphics.hpp>
#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Game/Resource/TextureService.hpp>

// https://www.reddit.com/r/gamedesign/s/2KBao2605y
// http://sokobano.de/wiki/index.php?title=How_to_play_Sokoban

int main()
{
    tokyo::Log::Info("http://sokobano.de/wiki/index.php?title=How_to_play_Sokoban\n");
    tokyo::Log::Info("https://www.reddit.com/r/gamedesign/s/2KBao2605y\n");

    auto window = sf::RenderWindow(sf::VideoMode({ 1280, 720 }), "Tokyo Sokoban");
    window.setVerticalSyncEnabled(true);

    tokyo::InputActionManager inputActionManager;
    tokyo::TextureService textureService;
    
    inputActionManager.RegisterInputActionType(
    { 
        .name = "LCLICK", 
        .mouseButton = sf::Mouse::Button::Left, 
        .actionType = tokyo::ActionType::MOUSE_BUTTON 
    });
    
    inputActionManager.RegisterInputActionType(
    { 
        .name = "SPACE", 
        .key = sf::Keyboard::Key::Space,
        .actionType = tokyo::ActionType::KEY 
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

        }

        inputActionManager.UpdateInputCache();

        window.clear(sf::Color::Cyan);

        // render
        {

        }

        window.display();
    }
    window.close();
}