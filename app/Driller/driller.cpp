#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/Application.hpp>
#include <tokyo/Driller/Scenes/SplashScene.hpp>
#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Driller/ManagerPackage.hpp>
#include <tokyo/Driller/ServicePackage.hpp>
#include <tokyo/Driller/Orchestration.hpp>
#include "DrillerConfig.hpp"

#include <thread>

int main(int _argc, char** _argv)
{
    std::cout << "TODO: Cancel action to remove job etc" << std::endl;
    std::cout << "TODO: Numkey to create build building job" << std::endl;
    
    tokyo::Application app;
    app.setName(drl::Constants::Title);

    drl::SplashScene splashScene;

    if (!app.startSplash(sf::VideoMode(), &splashScene))
    {
        return EXIT_FAILURE;
    }

    drl::ManagerPackage managers(app.getWindow());

    managers.fileManager.registerDirectory(drl::DrillerConfig::RootPath);

    drl::GameData gameData;

    drl::ServicePackage services(managers, gameData);

    const auto sleepTime = std::chrono::milliseconds(100);

    {
        std::this_thread::sleep_for(sleepTime);

        drl::Orchestration::InitialiseConfiguration(app, managers, services);
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(sleepTime);

        if (!drl::Orchestration::InitialiseTextures(managers))
        {
            return EXIT_FAILURE;
        }
    }
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    {
        std::this_thread::sleep_for(sleepTime);

        if (!drl::Orchestration::InitialiseFonts(managers))
        {
            return EXIT_FAILURE;
        }
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

    app.setName(managers.configManager.getTitle());

    {
        std::this_thread::sleep_for(sleepTime);
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

    drl::Orchestration::InitialiseInput(managers);

    drl::Orchestration::InitialiseGame(app, gameData, managers, services);

    app.start();

    return EXIT_SUCCESS;
}