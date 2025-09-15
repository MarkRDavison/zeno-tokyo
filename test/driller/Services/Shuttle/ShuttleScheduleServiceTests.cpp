#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttleScheduleService.hpp>


namespace drl
{
	namespace ShuttleScheduleServiceTests
	{

		struct Package
		{

			Package() :
				service(
					shuttleData,
					workerRecruitmentServiceMock.get(),
					workerCreationServiceMock.get(),
					shuttlePrototypeServiceMock.get()
				)
			{

			}

			ShuttleData shuttleData;
			fakeit::Mock<IWorkerRecruitmentService> workerRecruitmentServiceMock;
			fakeit::Mock<IWorkerCreationService> workerCreationServiceMock;
			fakeit::Mock<IShuttlePrototypeService> shuttlePrototypeServiceMock;

			ShuttleScheduleService service;

		};

		TEST_CASE("updateShuttle for idle shuttle", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};

			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::Idle;
			ShuttlePrototype p{};
			p.idleTime = 1.0f;

			SECTION("State remains in idle when no time has passed")
			{
				package.service.updateShuttle(0.0f, s, p);

				REQUIRE(ShuttleState::Idle == s.state);
				REQUIRE(0.0f == s.elapsed);
			}
			SECTION("State remains in idle when insufficient time has passed")
			{
				package.service.updateShuttle(0.5f, s, p);

				REQUIRE(ShuttleState::Idle == s.state);
				REQUIRE(0.5f == s.elapsed);
			}
			SECTION("State moves to travelling to surface when sufficient time has passed")
			{
				package.service.updateShuttle(1.0f, s, p);

				REQUIRE(ShuttleState::TravellingToSurface == s.state);
				REQUIRE(0.0f == s.elapsed);
			}

		}

		TEST_CASE("updateShuttle for travelling to surface shuttle", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};

			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::TravellingToSurface;
			s.surfacePosition = { 1.0f, 0.0f };
			ShuttlePrototype p{};
			p.speed = 1.0f;

			SECTION("State, elapsed time and position remain the same when no time has passed")
			{
				const auto originalPosition = s.position;

				package.service.updateShuttle(0.0f, s, p);

				REQUIRE(ShuttleState::TravellingToSurface == s.state);
				REQUIRE(0.0f == s.elapsed);
				REQUIRE(originalPosition == s.position);
			}

			SECTION("elapsed time and position update when time has passed")
			{
				const auto originalPosition = s.position;
				const float delta = 0.5f;

				package.service.updateShuttle(delta, s, p);

				REQUIRE(ShuttleState::TravellingToSurface == s.state);
				REQUIRE(delta == s.elapsed);
				REQUIRE(originalPosition != s.position);
			}

			SECTION("elapsed time, position and state update when enough time to reach target")
			{
				const auto originalPosition = s.position;
				const float delta = 1.0f;

				fakeit::When(
					Method(
						package.workerRecruitmentServiceMock,
						getRequiredWorkerTypes
					)
				).Return({});

				package.service.updateShuttle(delta, s, p);

				REQUIRE(ShuttleState::WaitingOnSurface == s.state);
				REQUIRE(0.0f == s.elapsed);
				REQUIRE(originalPosition != s.position);
			}
		}

		TEST_CASE("updateShuttle for waiting on surface shuttle", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};

			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::WaitingOnSurface;
			s.surfacePosition = { 1.0f, 0.0f };
			s.position = s.surfacePosition;
			ShuttlePrototype p{};
			p.speed = 1.0f;
			p.loadingTime = 1.0f;

			SECTION("State, elapsed time and position remain the same when no time has passed")
			{
				const auto originalPosition = s.position;

				package.service.updateShuttle(0.0f, s, p);

				REQUIRE(ShuttleState::WaitingOnSurface == s.state);
				REQUIRE(0.0f == s.elapsed);
				REQUIRE(originalPosition == s.position);
			}
			SECTION("State remains in waiting on surface when insufficient time has passed")
			{
				package.service.updateShuttle(0.5f, s, p);

				REQUIRE(ShuttleState::WaitingOnSurface == s.state);
				REQUIRE(0.5f == s.elapsed);
			}
			SECTION("State moves to leaving surface when sufficient time has passed")
			{
				package.service.updateShuttle(1.0f, s, p);

				REQUIRE(ShuttleState::LeavingSurface == s.state);
				REQUIRE(0.0f == s.elapsed);
			}
		}

		TEST_CASE("updateShuttle for leaving surface shuttle", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};

			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::LeavingSurface;
			s.leavingPosition = { 2.0f, 0.0f };
			s.surfacePosition = { 1.0f, 0.0f };
			s.position = s.surfacePosition;
			ShuttlePrototype p{};
			p.speed = 1.0f;

			SECTION("State, elapsed time and position remain the same when no time has passed")
			{
				const auto originalPosition = s.position;

				package.service.updateShuttle(0.0f, s, p);

				REQUIRE(ShuttleState::LeavingSurface == s.state);
				REQUIRE(0.0f == s.elapsed);
				REQUIRE(originalPosition == s.position);
			}

			SECTION("elapsed time and position update when time has passed")
			{
				const auto originalPosition = s.position;
				const float delta = 0.5f;

				package.service.updateShuttle(delta, s, p);

				REQUIRE(ShuttleState::LeavingSurface == s.state);
				REQUIRE(delta == s.elapsed);
				REQUIRE(originalPosition != s.position);
			}

			SECTION("elapsed time, position and state update when enough time to reach target")
			{
				const auto originalPosition = s.position;
				const float delta = 1.0f;

				package.service.updateShuttle(delta, s, p);

				REQUIRE(ShuttleState::Completed == s.state);
				REQUIRE(0.0f == s.elapsed);
				REQUIRE(originalPosition != s.position);
			}
		}

		TEST_CASE("updateShuttle for completed shuttle", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};

			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::Completed;
			s.startingPosition = { -22.0f,0.0f };
			ShuttlePrototype p{};

			SECTION("State becomes idle")
			{
				package.service.updateShuttle(0.0f, s, p);

				REQUIRE(ShuttleState::Idle == s.state);
				REQUIRE(s.startingPosition == s.position);
			}
		}

		TEST_CASE("moveShuttleTowardsLocation", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};

			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::Idle;
			ShuttlePrototype p{};
			p.speed = 1.0f;

			SECTION("No change when no time has passed")
			{
				const auto originalPosition = s.position;
				REQUIRE_FALSE(package.service.moveShuttleTowardsLocation(0.0f, s, p, { 1.0f, 0.0f }, ShuttleState::Completed));
				REQUIRE(originalPosition == s.position);
			}

			SECTION("Expected movement when time has passed")
			{
				REQUIRE_FALSE(package.service.moveShuttleTowardsLocation(1.0f, s, p, { 2.0f, 0.0f }, ShuttleState::Completed));
				REQUIRE(sf::Vector2f(p.speed, 0.0f) == s.position);
			}

			SECTION("Expected movement target is reached")
			{
				const sf::Vector2f target = { p.speed, 0.0f };
				const auto nextState = ShuttleState::Completed;
				REQUIRE(package.service.moveShuttleTowardsLocation(1.0f, s, p, target, nextState));
				REQUIRE(target == s.position);
				REQUIRE(nextState == s.state);
			}
		}

		TEST_CASE("updateShuttle when landing sees how many workers are needed", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};
			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::TravellingToSurface;
			s.surfacePosition = { 1.0f,0.0f };
			s.position = s.surfacePosition;
			ShuttlePrototype p{};
			p.speed = 1.0f;

			fakeit::When(
				Method(
					package.workerRecruitmentServiceMock,
					getRequiredWorkerTypes
				)
			).Return({});

			package.service.updateShuttle(1.0f, s, p);

			fakeit::Verify(
				Method(
					package.workerRecruitmentServiceMock,
					getRequiredWorkerTypes
				)).Once();
		}

		TEST_CASE("updateShuttle when landing reduces amount required for each", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};
			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::TravellingToSurface;
			s.surfacePosition = { 1.0f,0.0f };
			s.position = s.surfacePosition;
			ShuttlePrototype p{};
			p.speed = 1.0f;

			fakeit::When(
				Method(
					package.workerRecruitmentServiceMock,
					getRequiredWorkerTypes
				)
			).Return({ 1,2,3 });
			fakeit::When(
				ConstOverloadedMethod(
					package.workerRecruitmentServiceMock,
					getRequiredWorkerCount,
					int(WorkerPrototypeId)
				)
			).Return(1).Return(2).Return(3);
			fakeit::When(
				OverloadedMethod(
					package.workerRecruitmentServiceMock,
					reduceWorkerPrototypeRequirement,
					void(WorkerPrototypeId, int)
				)
			).Return().Return().Return();

			fakeit::When(
				Method(
					package.workerCreationServiceMock,
					createWorker
				)
			).AlwaysReturn(true);

			package.service.updateShuttle(1.0f, s, p);

			fakeit::Verify(
				ConstOverloadedMethod(
					package.workerRecruitmentServiceMock,
					getRequiredWorkerCount,
					int(WorkerPrototypeId)
				)).Exactly(3);
			fakeit::Verify(
				OverloadedMethod(
					package.workerRecruitmentServiceMock,
					reduceWorkerPrototypeRequirement,
					void(WorkerPrototypeId, int)
				)).Exactly(3);

			fakeit::Verify(
				Method(
					package.workerCreationServiceMock,
					createWorker
				)).Exactly(6);
		}

		TEST_CASE("updateShuttle when landing restores required worker amount if create worker fails", "[Core][Services][ShuttleScheduleService]")
		{
			Package package{};
			ShuttleInstance& s = package.shuttleData.shuttles.emplace_back();
			s.state = ShuttleState::TravellingToSurface;
			s.surfacePosition = { 1.0f,0.0f };
			s.position = s.surfacePosition;
			ShuttlePrototype p{};
			p.speed = 1.0f;

			fakeit::When(
				Method(
					package.workerRecruitmentServiceMock,
					getRequiredWorkerTypes
				)
			).Return({ 1 });
			fakeit::When(
				ConstOverloadedMethod(
					package.workerRecruitmentServiceMock,
					getRequiredWorkerCount,
					int(WorkerPrototypeId)
				)
			).Return(1);
			fakeit::When(
				OverloadedMethod(
					package.workerRecruitmentServiceMock,
					reduceWorkerPrototypeRequirement,
					void(WorkerPrototypeId, int)
				)
			).Return();
			fakeit::When(
				OverloadedMethod(
					package.workerRecruitmentServiceMock,
					registerWorkerPrototypeRequirement,
					void(WorkerPrototypeId, int)
				)
			).Return();

			fakeit::When(
				Method(
					package.workerCreationServiceMock,
					createWorker
				)
			).AlwaysReturn(false);

			package.service.updateShuttle(1.0f, s, p);

			fakeit::Verify(
				OverloadedMethod(
					package.workerRecruitmentServiceMock,
					registerWorkerPrototypeRequirement,
					void(WorkerPrototypeId, int)
				).Using(
					1, 1
				)).Once();
		}
	}
}