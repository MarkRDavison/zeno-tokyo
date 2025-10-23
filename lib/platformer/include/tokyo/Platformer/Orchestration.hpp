#pragma once

#include <tokyo/Game/Application.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Core/Infrastructure/LuaManager.hpp>
#include <tokyo/Core/Infrastructure/ConfigurationManager.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Core/Infrastructure/FontManager.hpp>
#include <tokyo/Platformer/Data/PlatformerInstanceData.hpp>

namespace plt
{

	class Orchestration
	{
		Orchestration() = delete;
		~Orchestration() = delete;
	public:
		static void InitialiseConfiguration(
			tokyo::Application& _app,
			tokyo::LuaManager& _luaManager,
			tokyo::ConfigurationManager& _configManager);

		static void InitialiseInput(
			tokyo::IInputActionManager& _inputActionManager);

		static void InitialiseFonts(
			tokyo::FontManager& _fontManager);

		static void InitialiseTextures(
			tokyo::TextureManager& _textureManager);

		static void InitialiseGame(
			PlatformerInstanceData& _instanceData);
	};

}