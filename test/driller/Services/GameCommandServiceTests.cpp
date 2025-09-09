#include <catch2/catch_test_macros.hpp>
#include <tokyo/Driller/Services/GameCommandService.hpp>
#include <fakeit.hpp>

namespace drl
{
	namespace test
	{

		struct Package
		{

			Package() : Package(0ll) {}
			Package(long long _startTick
			) :
				service(
					terrainAlterationServiceMock.get(),
					_startTick
				)
			{

			}

			fakeit::Mock<ITerrainAlterationService> terrainAlterationServiceMock;

			drl::GameCommandService service;

		};

		TEST_CASE("Default constructor creates service with starting tick of zero", "[Services][GameCommandService]")
		{
			Package package;

			REQUIRE(0ll == package.service.getCurrentTick());
		}

		TEST_CASE("Constructor creates service with starting tick as given", "[Services][GameCommandService]")
		{
			const long long StartTick = 65123ll;
			Package package(StartTick);

			REQUIRE(StartTick == package.service.getCurrentTick());
		}

		TEST_CASE("Tick increases the current tick by 1", "[Services][GameCommandService]")
		{
			Package package;

			package.service.tick();
			REQUIRE(1ll == package.service.getCurrentTick());

			package.service.tick();
			REQUIRE(2ll == package.service.getCurrentTick());
		}
	}
}