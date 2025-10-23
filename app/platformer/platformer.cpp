#include "PlatformerConfig.hpp"
#include <thread>
#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/InputManager.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Core/Infrastructure/FileManager.hpp>
#include <tokyo/Core/Infrastructure/LuaManager.hpp>
#include <tokyo/Platformer/Orchestration.hpp>

int main(int, char**)
{
	tokyo::Log::Error("TODO: Get multiple games playing in one window\n");

	tokyo::Application app;

	plt::PlatformerInstanceData pid;

	tokyo::InputManager inputManager(app.getWindow());
	tokyo::InputActionManager inputActionManager(inputManager);
	tokyo::FileManager fileManager;
	tokyo::LuaManager luaManager(fileManager);
	tokyo::ConfigurationManager configManager(luaManager);
	tokyo::FontManager fontManager(fileManager);
	tokyo::TextureManager textureManager(fileManager);

	fileManager.registerDirectory(plt::PlatformerConfig::RootPath);

	const auto sleepTime = std::chrono::milliseconds(100);

	{
		std::this_thread::sleep_for(sleepTime);

		plt::Orchestration::InitialiseConfiguration(
			app,
			luaManager,
			configManager);
	}

	{
		std::this_thread::sleep_for(sleepTime);

		plt::Orchestration::InitialiseInput(
			inputActionManager);
	}

	{
		std::this_thread::sleep_for(sleepTime);

		plt::Orchestration::InitialiseFonts(
			fontManager);
	}

	{
		std::this_thread::sleep_for(sleepTime);

		plt::Orchestration::InitialiseTextures(
			textureManager);
	}

	app.setName(configManager.getTitle());

	app.initialise(sf::VideoMode({
		configManager.getResolution().first,
		configManager.getResolution().second
	}));

	plt::Orchestration::InitialiseGame(pid);

	app.start();

	return EXIT_SUCCESS;
}