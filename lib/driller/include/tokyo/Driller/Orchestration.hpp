#pragma once

#include <tokyo/Game/Application.hpp>
#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Driller/ManagerPackage.hpp>
#include <tokyo/Driller/ServicePackage.hpp>

namespace drl
{
	class Orchestration
	{
		Orchestration() = delete;
	public:

		static void InitialiseConfiguration(tokyo::Application& _app, ManagerPackage& _managers, ServicePackage& _services);
		static bool InitialiseTextures(ManagerPackage& _managers);
		static bool InitialiseFonts(ManagerPackage& _managers);
		static void InitialiseInput(ManagerPackage& _managers);
		static void InitialiseGame(tokyo::Application& _app, drl::GameData& _gameData, ManagerPackage& _managers, ServicePackage& _services);
	};
}