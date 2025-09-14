#include <catch2/catch_test_macros.hpp>
#include <tokyo/Driller/Services/Worker/WorkerCreationService.hpp>
#include <SFML/System/Vector2.hpp>
#include <fakeit.hpp>

namespace drl
{
	namespace WorkerCreationServiceTests
	{

		struct Package
		{
			Package() :
				service(
					workerData,
					workerPrototypeServiceMock.get())
			{
			}

			WorkerData workerData;
			fakeit::Mock<WorkerPrototypeService> workerPrototypeServiceMock;

			WorkerCreationService service;
		};


		TEST_CASE("createWorker returns false when the prototype does not exist", "[Services][WorkerCreationService]")
		{
			Package package{};
			WorkerPrototypeId id{ 123 };
			const float x{ 0.0f };
			const float y{ 0.0f };

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					isPrototypeRegistered,
					bool(WorkerPrototypeId))
			).Return(false);

			REQUIRE_FALSE(package.service.createWorker(id, { x, y }));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					isPrototypeRegistered,
					bool(WorkerPrototypeId)
				).Using(
					id
				)).Once();
		}

		TEST_CASE("createWorker tries to get the prototype if told it exists", "[Services][WorkerCreationService]")
		{
			Package package{};
			WorkerPrototypeId id{ 123 };
			const float x{ 0.0f };
			const float y{ 0.0f };

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					isPrototypeRegistered,
					bool(WorkerPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock, 
					createInstanceById,
					WorkerInstance(WorkerPrototypeId))
			).Return({});

			REQUIRE(package.service.createWorker(id, { x, y }));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					createInstanceById,
					WorkerInstance(WorkerPrototypeId)
				).Using(
					id
				)).Once();
		}

		TEST_CASE("createWorker creates a worker", "[Services][WorkerCreationService]")
		{
			Package package{};
			WorkerPrototypeId id{ 123 };
			const float x{ 10.0f };
			const float y{ 10.0f };

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					isPrototypeRegistered,
					bool(WorkerPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					createInstanceById,
					WorkerInstance(WorkerPrototypeId))
			).Return({});

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					getPrototype,
					const WorkerPrototype & (WorkerPrototypeId)
				)
			).Return({});

			REQUIRE(package.service.createWorker(id, { x, y }));

			REQUIRE(1 == package.workerData.workers.size());
			REQUIRE(x == package.workerData.workers[0].position.x);
			REQUIRE(y == package.workerData.workers[0].position.y);

			fakeit::Verify(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					createInstanceById,
					WorkerInstance(WorkerPrototypeId)
				).Using(
					id
				)).Once();
		}

	}
}