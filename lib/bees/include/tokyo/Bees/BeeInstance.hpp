#pragma once

#include <tokyo/Core/Log.hpp>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Game/Application.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Core/Infrastructure/FontManager.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Core/Infrastructure/FileManager.hpp>
#include <tokyo/Bees/World/Level.hpp>
#include <tokyo/Bees/World/BeeGameTime.hpp>

namespace bee
{
	class BeeInstance : tokyo::NonCopyable
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

		BeeGameTime GameTime;
		tokyo::Application& _application;
		tokyo::InputManager InputManager;
		tokyo::InputActionManager InputActionManager;
		tokyo::FileManager FileManager;
		tokyo::FontManager FontManager;
		tokyo::TextureManager TextureManager;
		Level* ActiveLevel{ nullptr };

	private:
		static thread_local BeeInstance* _instance;
	};
}