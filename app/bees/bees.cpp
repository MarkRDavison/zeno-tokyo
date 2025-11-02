#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <tokyo/Bees/Constants.hpp>
#include "BeesConfig.hpp"
#include <tokyo/Bees/Scenes/SplashScene.hpp>
#include <tokyo/Bees/Scenes/GameScene.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <thread>

int main()
{

    tokyo::Application app;
    app.setName(bee::Constants::Title);

    bee::SplashScene splashScene;

    if (!app.startSplash(sf::VideoMode(), &splashScene))
    {
        return EXIT_FAILURE;
    }

    bee::BeeInstance::Initialise(app);

    {
        bee::BeeInstance::Get().FileManager.registerDirectory(bee::BeesConfig::RootPath);
    }

    const auto sleepTime = std::chrono::milliseconds(100);

    {
        std::this_thread::sleep_for(sleepTime);

        {
            bee::BeeInstance::Get().InputActionManager.registerAction(bee::Constants::Action_Left,
                {
                    .primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress,
                    .primaryKey = sf::Keyboard::Key::A
                });
            bee::BeeInstance::Get().InputActionManager.registerAction(bee::Constants::Action_Right,
                {
                    .primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress,
                    .primaryKey = sf::Keyboard::Key::D
                });
            bee::BeeInstance::Get().InputActionManager.registerAction(bee::Constants::Action_Up,
                {
                    .primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress,
                    .primaryKey = sf::Keyboard::Key::W
                });
            bee::BeeInstance::Get().InputActionManager.registerAction(bee::Constants::Action_Down,
                {
                    .primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress,
                    .primaryKey = sf::Keyboard::Key::S
                });
            bee::BeeInstance::Get().InputActionManager.registerAction(bee::Constants::Action_TEMP_Interact,
                {
                    .primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress,
                    .primaryKey = sf::Keyboard::Key::Space
                });

            
        }
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        if (!bee::BeeInstance::Get().TextureManager.loadTexture("/data/textures/hive.png", "hive") ||
            !bee::BeeInstance::Get().TextureManager.loadTexture("/data/textures/bee.png", "bee"))
        {
            return EXIT_FAILURE;
        }
        std::this_thread::sleep_for(sleepTime);
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        if (!bee::BeeInstance::Get().FontManager.loadFont("/data/fonts/arial.ttf", "arial"))
        {
            return EXIT_FAILURE;
        }
        std::this_thread::sleep_for(sleepTime);
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(sleepTime);
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(sleepTime);
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();
    
    {
        if (!app.splashFinished(sf::VideoMode({ 1280, 720 })))
        {
            return EXIT_FAILURE;
        }

        auto scene = new bee::GameScene();

        scene->start();
        app.setScene(scene);
        app.setAppSpeedMultiplier(1.0f);
    }

    app.start();

    return EXIT_SUCCESS;
}