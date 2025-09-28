#include <catch2/catch_test_macros.hpp>
#include <tokyo/Driller/Services/Job/JobAllocationService.hpp>
#include <fakeit.hpp>

namespace drl
{
	namespace JobAllocationServiceTests
	{

		struct Package
		{
			Package() :
				service(
					jobData,
					workerData,
					terrainAlterationServiceMock.get(),
					workerPrototypeServiceMock.get()
				)
			{
			}

			JobData jobData;
			WorkerData workerData;
			TerrainData terrainData;

			fakeit::Mock<ITerrainAlterationService> terrainAlterationServiceMock;
			fakeit::Mock<IWorkerPrototypeService> workerPrototypeServiceMock;

			JobAllocationService service;
		};

		TEST_CASE("allocate jobs does nothing with no entities", "[Services][JobAllocationService]")
		{
			Package package{};

			REQUIRE_NOTHROW(package.service.allocateJobs());
		}

		TEST_CASE("canWorkerPerformJob", "[Services][JobAllocationService]")
		{
			Package package{};

			WorkerPrototype wp{};
			package.terrainData.shaftLevel = 0;

			auto& j = package.jobData.jobs.emplace_back();
			j.Id = 22;
			j.prototypeId = 12362;
			j.tile = { 1,0 };
			auto& w = package.workerData.workers.emplace_back();
			w.Id = 43;
			w.prototypeId = 333;

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					getPrototype,
					const WorkerPrototype & (WorkerPrototypeId)
				)
			).Return(wp);

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					isPrototypeRegistered,
					bool(WorkerPrototypeId))
			).Return(true);

			fakeit::When(
				Method(
					package.terrainAlterationServiceMock,
					canTileBeReached
				)
			).Return(true);

			SECTION("Worker prototype doesn't exist")
			{
				fakeit::When(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						isPrototypeRegistered,
						bool(WorkerPrototypeId))
				).Return(false);

				REQUIRE_FALSE(package.service.canWorkerPerformJob(w, j));

				fakeit::Verify(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						isPrototypeRegistered,
						bool(WorkerPrototypeId)
					).Using(
						w.prototypeId
					)).Once();
			}

			SECTION("worker prototype is retrieved")
			{

				package.service.canWorkerPerformJob(w, j);

				fakeit::Verify(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						isPrototypeRegistered,
						bool(WorkerPrototypeId)
					).Using(
						w.prototypeId
					)).Once();
				fakeit::Verify(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						getPrototype,
						const WorkerPrototype & (WorkerPrototypeId)
					).Using(
						w.prototypeId
					)).Once();
			}

			SECTION("Worker cannot perform job if no valid jobs exist in prototype")
			{
				wp.validJobPrototypes.clear();
				fakeit::When(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						getPrototype,
						const WorkerPrototype & (WorkerPrototypeId)
					)
				).Return(wp);
				REQUIRE_FALSE(package.service.canWorkerPerformJob(w, j));
			}

			SECTION("Worker cannot perform job if no matching job exists in prototype")
			{
				wp.validJobPrototypes.insert("Dig");

				fakeit::When(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						getPrototype,
						const WorkerPrototype & (WorkerPrototypeId)
					)
				).Return(wp);
				fakeit::When(
					Method(
						package.workerPrototypeServiceMock,
						getPrototypeId
					)
				).Return(99999);

				REQUIRE_FALSE(package.service.canWorkerPerformJob(w, j));

				fakeit::Verify(
					Method(
						package.workerPrototypeServiceMock,
						getPrototypeId
					).Using(
						"Dig"
					)).Once();
			}

			SECTION("Worker can perform job if matching job exists in prototype")
			{
				wp.validJobPrototypes.insert("Dig");

				fakeit::When(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						getPrototype,
						const WorkerPrototype & (WorkerPrototypeId)
					)
				).Return(wp);
				fakeit::When(
					Method(
						package.workerPrototypeServiceMock,
						getPrototypeId
					)
				).Return(j.prototypeId);

				REQUIRE(package.service.canWorkerPerformJob(w, j));

				fakeit::Verify(
					Method(
						package.workerPrototypeServiceMock,
						getPrototypeId
					).Using(
						"Dig"
					)).Once();
			}

			SECTION("Worker cannot perform job if they cannot reach it")
			{
				wp.validJobPrototypes.insert("Dig");

				fakeit::When(
					ConstOverloadedMethod(
						package.workerPrototypeServiceMock,
						getPrototype,
						const WorkerPrototype & (WorkerPrototypeId)
					)
				).Return(wp);
				fakeit::When(
					Method(
						package.workerPrototypeServiceMock,
						getPrototypeId
					)
				).Return(j.prototypeId);

				package.terrainAlterationServiceMock.Reset();
				fakeit::When(
					Method(
						package.terrainAlterationServiceMock,
						canTileBeReached
					)
				).Return(false);

				j.tile = { 3,0 };

				REQUIRE_FALSE(package.service.canWorkerPerformJob(w, j));

				fakeit::Verify(
					Method(
						package.workerPrototypeServiceMock,
						getPrototypeId
					).Using(
						"Dig"
					)).Once();
			}
		}

		TEST_CASE("single job can be allocated to single worker", "[Services][JobAllocationService]")
		{
			Package package{};

			WorkerPrototype wp{};
			wp.validJobPrototypes = { "Dig" };

			auto& j = package.jobData.jobs.emplace_back();
			j.Id = 22;
			auto& w = package.workerData.workers.emplace_back();
			w.Id = 43;

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					isPrototypeRegistered,
					bool(WorkerPrototypeId))
			).Return(true);

			fakeit::When(
				Method(
					package.terrainAlterationServiceMock,
					canTileBeReached
				)
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.workerPrototypeServiceMock,
					getPrototype,
					const WorkerPrototype & (WorkerPrototypeId)
				)
			).Return(wp);

			fakeit::When(
				Method(
					package.workerPrototypeServiceMock,
					getPrototypeId
				)
			).Return(j.prototypeId);

			package.service.allocateJobs();

			REQUIRE(j.Id == w.allocatedJobId);
			REQUIRE(w.Id == j.allocatedWorkerId);
		}
	}
}