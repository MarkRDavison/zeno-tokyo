#include <catch2/catch_test_macros.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>
#include <SFML/System/Vector2.hpp>
#include <fakeit.hpp>

namespace drl
{
	namespace test
	{

		TEST_CASE("dig shaft at the start increases the number of terrain rows", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			REQUIRE(service.digShaft(0));
			REQUIRE(0 == terrainData.shaftLevel);
		}

		TEST_CASE("dig shaft at an unnacessable row does nothing", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			REQUIRE_FALSE(service.digShaft(1));
			REQUIRE(0 == terrainData.rows.size());
		}

		TEST_CASE("dig shaft at start doesnt create any further tiles", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			service.digShaft(0);
			TerrainRow& topRow = terrainData.rows[0];

			REQUIRE(0 == topRow.leftTiles.size());
			REQUIRE(0 == topRow.rightTiles.size());
		}

		TEST_CASE("dig tile at level where shaft reaches in the center returns false", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			service.digShaft(0);

			REQUIRE_FALSE(service.digTile(0, 0));
		}

		TEST_CASE("dig tile at level where shaft reaches at a tile that has already been dug out returns false", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			service.digShaft(0);
			service.digTile(0, -1);
			service.digTile(0, +1);

			REQUIRE_FALSE(service.digTile(0, -1));
			REQUIRE_FALSE(service.digTile(0, +1));
		}

		TEST_CASE("dig tile at level where shaft reaches at a tile that has not already been dug out returns true", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			service.digShaft(0);
			service.digTile(0, -1);
			service.digTile(0, +1);
			terrainData.getTile(0, -1).dugOut = true;
			terrainData.getTile(0, +1).dugOut = true;

			REQUIRE(service.digTile(0, -2));
			REQUIRE(service.digTile(0, +2));
		}

		TEST_CASE("dig tile at level where shaft reaches at a tile that has not already been dug out with multiple undug tiles inbetween returns false", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			service.digShaft(0);

			REQUIRE_FALSE(service.digTile(0, +3));
			REQUIRE_FALSE(service.digTile(0, -3));
		}

		TEST_CASE("is tile dug returns false when tile does not exist for left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 0 };

			service.digShaft(Coords.y);

			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("is tile dug returns false when tile does not exist for right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 0 };

			service.digShaft(Coords.y);

			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("is tile dug returns false when tile does exist but isn't dug for left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 0 };

			service.digShaft(Coords.y);
			terrainData.rows.back().leftTiles.emplace_back().dugOut = false;

			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("is tile dug returns false when tile does exist but isn't dug for right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 0 };

			service.digShaft(Coords.y);
			terrainData.rows.back().rightTiles.emplace_back().dugOut = false;

			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("is tile dug returns true when tile exists and is dug out for left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 0 };

			service.digShaft(Coords.y);
			terrainData.rows.back().leftTiles.emplace_back().dugOut = true;

			REQUIRE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("is tile dug returns true when tile exists and is dug out for right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 0 };

			service.digShaft(Coords.y);
			terrainData.rows.back().rightTiles.emplace_back().dugOut = true;

			REQUIRE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("does tile exist returns false when tile doesn't exist for left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 0 };

			service.digShaft(Coords.y);

			REQUIRE_FALSE(service.doesTileExist(Coords.y, Coords.x));
		}

		TEST_CASE("does tile exist returns false when tile doesn't exist for right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 0 };

			service.digShaft(Coords.y);

			REQUIRE_FALSE(service.doesTileExist(Coords.y, Coords.x));
		}

		TEST_CASE("does tile exist returns true when tile exists for left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 0 };

			service.digShaft(Coords.y);
			service.digTile(Coords.y, Coords.x);

			REQUIRE(service.doesTileExist(Coords.y, Coords.x));
		}

		TEST_CASE("does tile exist returns true when tile exists for right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 0 };

			service.digShaft(Coords.y);
			service.digTile(Coords.y, Coords.x);

			REQUIRE(service.doesTileExist(Coords.y, Coords.x));
		}

		TEST_CASE("getTile returns the tile as expected for the left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 0 };

			service.digShaft(Coords.y);
			service.digTile(Coords.y, Coords.x);

			REQUIRE(&terrainData.getTile(Coords.y, Coords.x) == &service.getTile(Coords.y, Coords.x));
		}

		TEST_CASE("getTile returns the tile as expected for the right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 0 };

			service.digShaft(Coords.y);
			service.digTile(Coords.y, Coords.x);

			REQUIRE(&terrainData.getTile(Coords.y, Coords.x) == &service.getTile(Coords.y, Coords.x));
		}

		TEST_CASE("initialiseTile creates a new tile with default values for a row that exists on the left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 0 };

			service.digShaft(Coords.y);

			service.initialiseTile(Coords.y, Coords.x);

			REQUIRE(service.doesTileExist(Coords.y, Coords.x));
			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("initialiseTile creates a new tile with default values for a row that exists on the right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 0 };

			service.digShaft(Coords.y);

			service.initialiseTile(Coords.y, Coords.x);

			REQUIRE(service.doesTileExist(Coords.y, Coords.x));
			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("initialiseTile creates a new tile with default values for a row that does not exist on the left", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ -1, 1 };

			service.digShaft(Coords.y);

			service.initialiseTile(Coords.y, Coords.x);

			REQUIRE(service.doesTileExist(Coords.y, Coords.x));
			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("initialiseTile creates a new tile with default values for a row that does not exist on the right", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			const sf::Vector2i Coords{ +1, 1 };

			service.digShaft(Coords.y);

			service.initialiseTile(Coords.y, Coords.x);

			REQUIRE(service.doesTileExist(Coords.y, Coords.x));
			REQUIRE_FALSE(service.isTileDugOut(Coords.y, Coords.x));
		}

		TEST_CASE("doesLevelExist returns true when asking about level that exists", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);
			terrainData.shaftLevel = 0;

			REQUIRE(service.doesLevelExist(0));
		}

		TEST_CASE("doesLevelExist returns false when asking about level that does not exist", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			REQUIRE_FALSE(service.doesLevelExist(0));

			terrainData.rows.emplace_back();

			REQUIRE_FALSE(service.doesLevelExist(1));
		}

		TEST_CASE("canTileBeReached returns true for the surface", "[Services][TerrainAlterationService]")
		{
			TerrainData terrainData{};
			TerrainAlterationService service(terrainData);

			REQUIRE(service.canTileBeReached(-1, -15));
			REQUIRE(service.canTileBeReached(-1, +15));
		}

	}
}