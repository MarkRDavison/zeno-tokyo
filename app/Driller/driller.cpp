#include <SFML/Graphics.hpp>
#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Game/Resource/TextureService.hpp>
#include <tokyo/Game/Application.hpp>
#include "Scenes/SplashScene.hpp"

int main(int _argc, char** _argv)
{
    tokyo::Application app;

    drl::SplashScene splashScene;

    if (!app.startSplash(sf::VideoMode(), &splashScene))
    {
        return EXIT_FAILURE;
    }

    // Start doing stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Finish doing stuff
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    if (!app.splashFinished(sf::VideoMode({ 1280, 720 })))
    {
        return EXIT_FAILURE;
    }

    app.start();

    return EXIT_SUCCESS;
}