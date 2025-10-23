#pragma once

#include <tokyo/Core/Log.hpp>
#include <tokyo/Game/Application.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Core/Infrastructure/FileManager.hpp>

namespace bee
{
	class BeeInstance
	{
	public:
		static BeeInstance& Get()
		{
			if (_instance == nullptr)
			{
				tokyo::Log::Error("Must initialise the instance before retrieving.\n");
				throw std::runtime_error("Must initialise the instance before retrieving.");
			}

			return *_instance;
		}

		static void Initialise(tokyo::Application& application) 
		{
			if (_instance != nullptr)
			{
				tokyo::Log::Error("Must not initialise the instance more than once.\n");
				throw std::runtime_error("Must not initialise the instance more than once.");
			}

			_instance = new BeeInstance(application);
		}

	public:
		BeeInstance(
			tokyo::Application& application);

		tokyo::InputManager InputManager;
		tokyo::InputActionManager InputActionManager;
		tokyo::FileManager FileManager;

	private:
		static BeeInstance* _instance;
		tokyo::Application& _application;
	};
}