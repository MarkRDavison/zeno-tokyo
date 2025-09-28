#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>
#include <tokyo/Driller/Services/Worker/WorkerJobUpdateService.hpp>

namespace drl
{
	namespace WorkerJobUpdateServiceTests
	{

		struct Package
		{
			Package() :
				service(
					workerData,
					jobData,
					terrainAlterationServiceMock.get(),
					jobPrototypeServiceMock.get()
				)
			{
			}

			WorkerData workerData;
			JobData jobData;
			fakeit::Mock<ITerrainAlterationService> terrainAlterationServiceMock;
			fakeit::Mock<JobPrototypeService> jobPrototypeServiceMock;

			WorkerJobUpdateService service;
		};

		TEST_CASE("updateWorkerJob decreases amount of work remaining on job", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			JobPrototype jp{};
			jp.work = 3.0f;
			jp.repeats = false;

			Tile t;

			auto& j = package.jobData.jobs.emplace_back();
			auto& w = package.workerData.workers.emplace_back();
			j.Id = 1;
			w.Id = 22;
			w.allocatedJobId = j.Id;
			j.allocatedWorkerId = w.Id;
			j.work = jp.work;

			fakeit::When(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			)).Return(jp);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			const float delta = 1.0f;

			package.service.updateWorkerJob(delta, w, j);

			REQUIRE(j.work == 2.0f);

			package.service.updateWorkerJob(delta, w, j);

			REQUIRE(j.work == 1.0f);

			package.service.updateWorkerJob(delta, w, j);

			REQUIRE(j.work == 0.0f);
		}

		TEST_CASE("updateWorkerJob sets job to require removal when work remaining <= 0", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			JobPrototype jp{};
			jp.work = 3.0f;
			jp.repeats = false;

			Tile t;

			auto& j = package.jobData.jobs.emplace_back();
			auto& w = package.workerData.workers.emplace_back();
			j.Id = 1;
			w.Id = 22;
			w.allocatedJobId = j.Id;
			j.allocatedWorkerId = w.Id;
			j.work = jp.work;

			fakeit::When(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			)).Return(jp);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			package.service.updateWorkerJob(jp.work, w, j);

			REQUIRE(j.requiresRemoval);
		}

		TEST_CASE("updateWorkerJob removes association with worker and sets worker to idle when non repeating job completes", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			JobPrototype jp{};
			jp.work = 3.0f;
			jp.repeats = false;

			Tile t;

			auto& j = package.jobData.jobs.emplace_back();
			auto& w = package.workerData.workers.emplace_back();
			j.Id = 1;
			w.Id = 22;
			w.allocatedJobId = j.Id;
			j.allocatedWorkerId = w.Id;
			j.work = jp.work;
			w.state = WorkerState::WorkingJob;

			fakeit::When(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			)).Return(jp);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			package.service.updateWorkerJob(jp.work, w, j);

			REQUIRE(0 == w.allocatedJobId);
			REQUIRE(WorkerState::Idle == w.state);


			fakeit::Verify(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				).Using(
					j.tile.y,
					j.tile.x
				)).Once();
		}

		TEST_CASE("updateWorkerJob does not remove association with worker when non repeating job completes", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			JobPrototype jp{};
			jp.work = 3.0f;
			jp.repeats = true;

			auto& j = package.jobData.jobs.emplace_back();
			auto& w = package.workerData.workers.emplace_back();
			j.Id = 1;
			w.Id = 22;
			w.allocatedJobId = j.Id;
			j.allocatedWorkerId = w.Id;
			j.work = jp.work;

			fakeit::When(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			)).Return(jp);

			package.service.updateWorkerJob(jp.work, w, j);

			REQUIRE(0 != w.allocatedJobId);
		}

		TEST_CASE("updateWorkerJob when job prototype repeats the job instance work increases", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			JobPrototype jp{};
			jp.work = 3.0f;
			jp.repeats = true;

			auto& j = package.jobData.jobs.emplace_back();
			auto& w = package.workerData.workers.emplace_back();
			j.Id = 1;
			w.Id = 22;
			w.allocatedJobId = j.Id;
			j.allocatedWorkerId = w.Id;
			j.work = jp.work;

			fakeit::When(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			)).Return(jp);

			package.service.updateWorkerJob(jp.work / 2.0f, w, j);
			REQUIRE(j.work == jp.work / 2.0f);
			package.service.updateWorkerJob(jp.work / 2.0f, w, j);
			REQUIRE(j.work == jp.work);

			fakeit::Verify(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			).Using(
				j.prototypeId
			)).Once();
		}

		TEST_CASE("updateWorkerJob invokes prototype onComplete when completed with non repeating job", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			bool callbackInvoked = false;

			Tile t;

			JobPrototype jp{};
			jp.work = 3.0f;
			jp.repeats = false;
			jp.onComplete =
				[&callbackInvoked](const JobInstance&) -> void
				{
					callbackInvoked = true;
				};

			auto& j = package.jobData.jobs.emplace_back();
			auto& w = package.workerData.workers.emplace_back();
			j.Id = 1;
			w.Id = 22;
			w.allocatedJobId = j.Id;
			j.allocatedWorkerId = w.Id;
			j.work = jp.work;

			fakeit::When(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			)).Return(jp);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			package.service.updateWorkerJob(jp.work, w, j);

			REQUIRE(callbackInvoked);
		}

		TEST_CASE("updateWorkerJob invokes prototype onComplete when completed with repeating job", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			int callbackInvokedCount = 0;

			JobPrototype jp{};
			jp.work = 3.0f;
			jp.repeats = true;
			jp.onComplete =
				[&callbackInvokedCount](const JobInstance&) -> void
				{
					callbackInvokedCount++;
				};

			auto& j = package.jobData.jobs.emplace_back();
			auto& w = package.workerData.workers.emplace_back();
			j.Id = 1;
			w.Id = 22;
			w.allocatedJobId = j.Id;
			j.allocatedWorkerId = w.Id;
			j.work = jp.work;

			fakeit::When(ConstOverloadedMethod(
				package.jobPrototypeServiceMock,
				getPrototype,
				const JobPrototype & (JobPrototypeId)
			)).AlwaysReturn(jp);

			package.service.updateWorkerJob(jp.work, w, j);

			REQUIRE(1 == callbackInvokedCount);

			package.service.updateWorkerJob(jp.work, w, j);

			REQUIRE(2 == callbackInvokedCount);

			package.service.updateWorkerJob(jp.work, w, j);

			REQUIRE(3 == callbackInvokedCount);
		}

		TEST_CASE("removeCompletedJobs removes jobs where requiresRemoval == true", "[Services][WorkerJobUpdateService]")
		{
			Package package{};

			package.jobData.jobs.emplace_back(); package.jobData.jobs.back().requiresRemoval = false;
			package.jobData.jobs.emplace_back(); package.jobData.jobs.back().requiresRemoval = true;
			package.jobData.jobs.emplace_back(); package.jobData.jobs.back().requiresRemoval = false;
			package.jobData.jobs.emplace_back(); package.jobData.jobs.back().requiresRemoval = true;

			package.service.removeCompletedJobs();

			REQUIRE(2 == package.jobData.jobs.size());
		}
	}
}