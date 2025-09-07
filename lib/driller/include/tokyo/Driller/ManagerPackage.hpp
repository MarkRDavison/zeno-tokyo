#pragma once

#include <tokyo/Core/Infrastructure/ConfigurationManager.hpp>
#include <tokyo/Core/Infrastructure/LuaManager.hpp>
#include <tokyo/Core/Infrastructure/FileManager.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Core/Infrastructure/FontManager.hpp>
#include <tokyo/Game/InputActionManager.hpp>

namespace drl
{
	class ManagerPackage
	{
	public:
        ManagerPackage(
            const sf::Window& _window
        ) :
            inputManager(_window),
            inputActionManager(inputManager),
            fileManager(),
            luaManager(fileManager),
            configManager(luaManager),
            fontManager(fileManager),
            textureManager(fileManager)
        {

        }

        tokyo::InputManager inputManager;
        tokyo::InputActionManager inputActionManager;
        tokyo::FileManager fileManager;
        tokyo::LuaManager luaManager;
        tokyo::ConfigurationManager configManager;
        tokyo::FontManager fontManager;
        tokyo::TextureManager textureManager;
	};
}