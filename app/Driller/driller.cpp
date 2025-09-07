#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/Application.hpp>
#include "Scenes/SplashScene.hpp"
#include "Constants.hpp"
#include "ManagerPackage.hpp"
#include "ServicePackage.hpp"

int main(int _argc, char** _argv)
{
    tokyo::Application app;
    app.setName(drl::Constants::Title);

    drl::SplashScene splashScene;

    if (!app.startSplash(sf::VideoMode(), &splashScene))
    {
        return EXIT_FAILURE;
    }

    drl::ManagerPackage managers(app.getWindow());

    managers.fileManager.registerDirectory("F:/Workspace/Github/zeno-tokyo/app/Driller");

    drl::ServicePackage services(managers);

    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        managers.configManager.loadConfiguration("/data/Scripts/config.lua");
        auto& state = managers.luaManager.getState(tokyo::LuaManager::DefaultStateScope);
        state.set_function("exit", &tokyo::Application::stop, &app);
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!managers.textureManager.loadTexture("./data/Textures/tile_sprite_sheet.png", drl::Constants::TileSpriteSheetTextureName))
        {
            return EXIT_FAILURE;
        }
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!managers.fontManager.loadFont("/data/Fonts/arial.ttf", "DEBUG"))
        {
            return EXIT_FAILURE;
        }
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    app.setName(managers.configManager.getTitle());

    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    if (!app.splashFinished(sf::VideoMode(
        { 
            managers.configManager.getResolution().first,
            managers.configManager.getResolution().second
        }
    )))
    {
        return EXIT_FAILURE;
    }

    {
        {
            tokyo::InputAction action;
            action.primaryActivationType = tokyo::InputAction::InputActivationType::MouseButtonPress;
            action.primaryButton = sf::Mouse::Button::Left;
            managers.inputActionManager.registerAction(drl::Constants::ClickActionName, action);
        }
        {
            tokyo::InputAction action;
            action.primaryActivationType = tokyo::InputAction::InputActivationType::KeyPress;
            action.primaryKey = sf::Keyboard::Key::Escape;
            managers.inputActionManager.registerAction(drl::Constants::CancelActionName, action);
        }
    }

    app.start();

    return EXIT_SUCCESS;
}