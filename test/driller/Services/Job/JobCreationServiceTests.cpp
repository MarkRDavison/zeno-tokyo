#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>
#include <tokyo/Driller/Services/Job/JobCreationService.hpp>

namespace drl
{
	namespace JobCreationServiceTests
	{

		struct Package
		{
			Package() :
				service(
					jobData,
					jobPrototypeServiceMock.get(),
					terrainAlterationServiceMock.get())
			{
			}

			JobData jobData;
			fakeit::Mock<JobPrototypeService> jobPrototypeServiceMock;
			fakeit::Mock<ITerrainAlterationService> terrainAlterationServiceMock;

			JobCreationService service;
		};


		TEST_CASE("createJob returns false when the prototype does not exist", "[Services][JobCreationService]")
		{
			Package package{};
			JobPrototypeId id{ 123 };
			JobPrototypeId idAdditional{ 124 };

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					isPrototypeRegistered,
					bool(JobPrototypeId))
			).Return(false);

			REQUIRE_FALSE(package.service.createJob(id, idAdditional, { 0, 0 }));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					isPrototypeRegistered,
					bool(JobPrototypeId)
				).Using(
					id
				)).Once();
		}

		TEST_CASE("createJob tries to get the prototype if told it exists", "[Services][JobCreationService]")
		{
			Package package{};
			JobPrototypeId id{ 123 };
			JobPrototypeId idAdditional{ 124 };
			Tile t;

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					isPrototypeRegistered,
					bool(JobPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					getPrototype,
					const JobPrototype & (JobPrototypeId)
				)
			).Return({});

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					createInstanceById,
					JobInstance(JobPrototypeId))
			).Return({});

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			REQUIRE(package.service.createJob(id, idAdditional, { 0, 0 }));

			fakeit::Verify(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					getPrototype,
					const JobPrototype & (JobPrototypeId)
				).Using(
					id
				)).Once();
		}

		TEST_CASE("createJob creates a job", "[Services][JobCreationService]")
		{
			Package package{};
			JobPrototypeId id{ 123 };
			JobPrototypeId idAdditional{ 124 };
			Tile t;

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					isPrototypeRegistered,
					bool(JobPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					createInstanceById,
					JobInstance(JobPrototypeId))
			).Return({});

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					getPrototype,
					const JobPrototype & (JobPrototypeId)
				)
			).Return({});

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			REQUIRE(package.service.createJob(id, idAdditional, { 10, 10 }));

			REQUIRE(1 == package.jobData.jobs.size());
			REQUIRE(idAdditional == package.jobData.jobs[0].additionalPrototypeId);
			REQUIRE(10 == package.jobData.jobs[0].tile.x);
			REQUIRE(10 == package.jobData.jobs[0].tile.y);

			fakeit::Verify(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					createInstanceById,
					JobInstance(JobPrototypeId)
				).Using(
					id
				)).Once();
		}

		TEST_CASE("createJob doesn't create a job if the tile already has an allocated job id", "[Services][JobCreationService]")
		{
			Package package{};
			JobPrototypeId id{ 123 };
			JobPrototypeId idAdditional{ 124 };
			Tile t;
			t.jobReserved = true;

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					isPrototypeRegistered,
					bool(JobPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					createInstanceById,
					JobInstance(JobPrototypeId))
			).Return({});

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					getPrototype,
					const JobPrototype & (JobPrototypeId)
				)
			).Return({});

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			REQUIRE_FALSE(package.service.createJob(id, idAdditional, { 10, 10 }));
		}

		TEST_CASE("createJob creates a job using the calculateOffset method", "[Services][JobCreationService]")
		{
			Package package{};
			JobPrototypeId id{ 123 };
			JobPrototypeId idAdditional{ 124 };
			JobPrototype p;
			Tile t;
			sf::Vector2f offset = { 1.0f, 2.0f };
			p.calculateOffset = [&](JobInstance, JobPrototype) -> sf::Vector2f
				{
					return offset;
				};

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					isPrototypeRegistered,
					bool(JobPrototypeId))
			).Return(true);

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					createInstanceById,
					JobInstance(JobPrototypeId))
			).Return({});

			fakeit::When(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					getPrototype,
					const JobPrototype & (JobPrototypeId)
				)
			).Return(p);

			fakeit::When(
				OverloadedMethod(
					package.terrainAlterationServiceMock,
					getTile,
					Tile & (int, int)
				)
			).Return(t);

			REQUIRE(package.service.createJob(id, idAdditional, { 10, 10 }));

			REQUIRE(1 == package.jobData.jobs.size());
			REQUIRE(idAdditional == package.jobData.jobs[0].additionalPrototypeId);
			REQUIRE(10 == package.jobData.jobs[0].tile.x);
			REQUIRE(10 == package.jobData.jobs[0].tile.y);
			REQUIRE(offset == package.jobData.jobs[0].offset);

			fakeit::Verify(
				ConstOverloadedMethod(
					package.jobPrototypeServiceMock,
					createInstanceById,
					JobInstance(JobPrototypeId)
				).Using(
					id
				)).Once();
		}

	}
}