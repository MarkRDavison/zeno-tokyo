#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttleCreationService.hpp>

namespace drl
{
	namespace ShuttleCreationServiceTests
	{

		struct Package
		{

			Package() :
				service(
					shuttleData,
					shuttlePrototypeServiceMock.get()
				)
			{

			}

			ShuttleData shuttleData;
			fakeit::Mock<IShuttlePrototypeService> shuttlePrototypeServiceMock;

			ShuttleCreationService service;

		};

		TEST_CASE("createShuttle returns false when the prototype does not exist", "[Core][Services][ShuttleCreationService]")
		{
			Package package{};
			ShuttlePrototypeId id{ 123 };

			fakeit::When(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					isPrototypeRegistered,
					bool(ShuttlePrototypeId))
			).Return(false);

			REQUIRE_FALSE(package.service.createShuttle(id));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					isPrototypeRegistered,
					bool(ShuttlePrototypeId)
				).Using(
					id
				)).Once();
		}

		TEST_CASE("createShuttle tries to get the prototype if told it exists", "[Core][Services][ShuttleCreationService]")
		{
			Package package{};
			ShuttlePrototypeId id{ 123 };

			fakeit::When(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					isPrototypeRegistered,
					bool(ShuttlePrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					getPrototype,
					const ShuttlePrototype & (ShuttlePrototypeId)
				)
			).Return({});

			fakeit::When(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					createInstanceById,
					ShuttleInstance(ShuttlePrototypeId))
			).Return({});

			REQUIRE(package.service.createShuttle(id));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					getPrototype,
					const ShuttlePrototype & (ShuttlePrototypeId)
				).Using(
					id
				)).Once();
		}

		TEST_CASE("createShuttle creates a shuttle", "[Core][Services][ShuttleCreationService]")
		{
			Package package{};
			ShuttlePrototypeId id{ 123 };

			fakeit::When(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					isPrototypeRegistered,
					bool(ShuttlePrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					createInstanceById,
					ShuttleInstance(ShuttlePrototypeId))
			).Return({});

			fakeit::When(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					getPrototype,
					const ShuttlePrototype & (ShuttlePrototypeId)
				)
			).Return({});

			REQUIRE(package.service.createShuttle(id));

			REQUIRE(1 == package.shuttleData.shuttles.size());

			fakeit::Verify(
				ConstOverloadedMethod(
					package.shuttlePrototypeServiceMock,
					createInstanceById,
					ShuttleInstance(ShuttlePrototypeId)
				).Using(
					id
				)).Once();
		}

	}
}