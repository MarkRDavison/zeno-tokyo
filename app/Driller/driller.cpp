#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/Application.hpp>
#include <tokyo/Driller/Scenes/SplashScene.hpp>
#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Driller/ManagerPackage.hpp>
#include <tokyo/Driller/ServicePackage.hpp>
#include <tokyo/Driller/Orchestration.hpp>

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

    // TODO: way to set this from cmake based on build type and source directory...
    managers.fileManager.registerDirectory("F:/Workspace/Github/zeno-tokyo/app/Driller");

    drl::GameData gameData;
    // TODO: REPLACE with dig shaft command and terrain alteration service
    gameData.terrain.rows.emplace_back();
    gameData.terrain.shaftLevel++;
    gameData.terrain.rows.emplace_back();
    gameData.terrain.shaftLevel++;

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

    // managers.luaManager.runScriptFile("/data/Scripts/Base/initializeCommands.lua");

    drl::Orchestration::InitialiseGame(app, gameData, managers, services);

    app.start();

    // TODO: Scene lifecycle

    return EXIT_SUCCESS;
}