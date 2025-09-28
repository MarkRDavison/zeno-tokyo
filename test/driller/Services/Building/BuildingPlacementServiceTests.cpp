#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>
#include <tokyo/Driller/Services/Building/BuildingPlacementService.hpp>
#include <tokyo/Driller/Core/GameCommand.hpp>

namespace drl
{
	namespace BuildingPlacementServiceTests
	{

		struct Package
		{

			Package() :
				service(
					buildingData,
					terrainAlterationServiceMock.get(),
					workerRecruitmentServiceMock.get(),
					jobCreationServiceMock.get(),
					buildingPrototypeServiceMock.get()
				)
			{

			}

			BuildingData buildingData;
			fakeit::Mock<ITerrainAlterationService> terrainAlterationServiceMock;
			fakeit::Mock<IBuildingPrototypeService> buildingPrototypeServiceMock;
			fakeit::Mock<IJobCreationService> jobCreationServiceMock;
			fakeit::Mock<IWorkerRecruitmentService> workerRecruitmentServiceMock;

			BuildingPlacementService service;

		};

		TEST_CASE("canPlacePrototype returns false when the prototype does not exist", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(false);

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Once();
		}

		TEST_CASE("canPlacePrototype tries to get the prototype if told it exists", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return({});

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(false);

			REQUIRE_NOTHROW(package.service.canPlacePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Once();
		}

		TEST_CASE("canPlacePrototype returns false if the prototype is build over non existant tiles", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(false);

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Once();
		}

		TEST_CASE("canPlacePrototype returns false if the prototype is build over a non dug out tile", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = false;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t);

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Once();
		}

		TEST_CASE("canPlacePrototype returns false if the prototype is build over a tile with an existing building", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = true;
			t.hasBuilding = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t);

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Once();
		}

		TEST_CASE("canPlacePrototype returns false if the prototype is build over a tile with a reserved job", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = true;
			t.jobReserved = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t);

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Once();
		}

		TEST_CASE("canPlacePrototype returns true if the prototype is build over a valid tile", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t);

			REQUIRE(package.service.canPlacePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Once();
		}

		TEST_CASE("placePrototype returns false if the prototype cannot be placed", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = true;
			t.jobReserved = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t);

			REQUIRE_FALSE(package.service.placePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Once();
		}

		TEST_CASE("placePrototype returns true if the prototype can be placed", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					createInstanceById,
					BuildingInstance(BuildingPrototypeId))
			).Return(BuildingInstance{});

			REQUIRE(package.service.placePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Twice();
		}

		TEST_CASE("placePrototype creates an instance with the correct location if the prototype can be placed", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					createInstanceById,
					BuildingInstance(BuildingPrototypeId))
			).Return(BuildingInstance{});

			REQUIRE(package.service.placePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));
			REQUIRE(1 == package.buildingData.buildings.size());
			REQUIRE(sf::Vector2i(placeBuilding.column, placeBuilding.level) == package.buildingData.buildings[0].coordinates);
		}

		TEST_CASE("placePrototype updates the tile alteration service with the new building", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };

			Tile t;
			t.dugOut = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					const Tile & (int, int))
			).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					createInstanceById,
					BuildingInstance(BuildingPrototypeId))
			).Return({});

			REQUIRE(package.service.placePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));
			REQUIRE(t.hasBuilding);
		}

		TEST_CASE("placePrototype registers the required workers", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const std::string WorkerPrototypeName = "Miner";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };
			p.requiredWorkers = {
				{ WorkerPrototypeName, 2 }
			};

			Tile t;
			t.dugOut = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					const Tile & (int, int))
			).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					createInstanceById,
					BuildingInstance(BuildingPrototypeId))
			).Return({});

			fakeit::When(
				OverloadedMethod(
					package.workerRecruitmentServiceMock,
					registerWorkerPrototypeRequirement,
					void(const std::string&, int)
				)
			).Return();

			REQUIRE(package.service.placePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.workerRecruitmentServiceMock,
					registerWorkerPrototypeRequirement,
					void(const std::string&, int)
				).Using(
					WorkerPrototypeName,
					p.requiredWorkers[WorkerPrototypeName]
				)).Once();
		}

		TEST_CASE("placePrototype creates the provided jobs", "[Core][Services][BuildingPlacementService]")
		{
			Package package{};

			const std::string PrototypeName = "Name";
			const std::string WorkerPrototypeName = "Miner";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
			BuildingPrototype p;
			p.name = PrototypeName;
			p.size = { 1,1 };
			p.providedJobs = {
				{ "Job_Mine", sf::Vector2f(0, 0) },
				{ "Job_Mine", sf::Vector2f(1, 0) }
			};

			Tile t;
			t.dugOut = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					isPrototypeRegistered,
					bool(BuildingPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					getPrototype,
					const BuildingPrototype & (BuildingPrototypeId))
			).Return(p).Return(p);

			fakeit::When(
				Method(package.terrainAlterationServiceMock, doesTileExist)
			).Return(true).Return(true);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int))
			).Return(t).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					const Tile & (int, int))
			).Return(t);

			fakeit::When(
				ConstOverloadedMethod(
					package.buildingPrototypeServiceMock,
					createInstanceById,
					BuildingInstance(BuildingPrototypeId))
			).Return({});

			fakeit::When(
				OverloadedMethod(
					package.jobCreationServiceMock,
					createJob,
					bool(const std::string&, sf::Vector2f, sf::Vector2i))
			).AlwaysReturn(true);

			REQUIRE(package.service.placePrototype(placeBuilding.prototypeId, placeBuilding.level, placeBuilding.column));

			fakeit::Verify(
				OverloadedMethod(
					package.jobCreationServiceMock,
					createJob,
					bool(const std::string&, sf::Vector2f, sf::Vector2i)
				)).Twice();
		}

	}
}