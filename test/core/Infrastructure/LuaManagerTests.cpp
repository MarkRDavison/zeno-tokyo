#include <catch2/catch_test_macros.hpp>
#include <tokyo/Core/Infrastructure/LuaManager.hpp>

namespace tokyo
{
    TEST_CASE("Can create and destroy manager", "[Infrastructure][LuaManager][Scripting]")
    {
        LuaManager manager;

        manager.initialise();

        manager.cleanup();
    }

    TEST_CASE("Can use basic lua logic", "[Infrastructure][LuaManager][Scripting]")
    {
        LuaManager manager;

        manager.initialise();

        manager.runScript("a,b=1,2;");

        const auto& state = manager.getState(LuaManager::DefaultStateScope);

        int a = state["a"];
        
        REQUIRE(1 == a);

        int b = state["b"];

        REQUIRE(2 == b);

        manager.cleanup();
    }
}