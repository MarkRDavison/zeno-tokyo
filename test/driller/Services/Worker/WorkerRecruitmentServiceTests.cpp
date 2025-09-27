#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>
#include <tokyo/Driller/Services/Worker/WorkerRecruitmentService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>

namespace drl
{
	namespace WorkerRecruitmentServiceTests
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

			WorkerRecruitmentService service;
		};

		TEST_CASE("registerWorkerPrototypeRequirement where current data does not exist creates it", "[Services][WorkerRecruitmentService]")
		{
			Package package{};
			const std::string workerName = "Builder";
			const WorkerPrototypeId prototypeId = 231;
			const int amount = 22;

			fakeit::When(
				Method(
					package.workerPrototypeServiceMock,
					getPrototypeId
				)
			).Return(prototypeId);

			package.service.registerWorkerPrototypeRequirement(workerName, amount);

			REQUIRE(package.workerData.requiredWorkers.count(prototypeId) > 0);
			REQUIRE(amount == package.workerData.requiredWorkers.at(prototypeId));
		}

		TEST_CASE("registerWorkerPrototypeRequirement where current data exists adds to it", "[Services][WorkerRecruitmentService]")
		{
			Package package{};
			const std::string workerName = "Builder";
			const WorkerPrototypeId prototypeId = 231;
			const int originalAmount = 22;
			const int amount = 21;
			package.workerData.requiredWorkers[prototypeId] = originalAmount;

			fakeit::When(
				Method(
					package.workerPrototypeServiceMock,
					getPrototypeId
				)
			).Return(prototypeId);

			package.service.registerWorkerPrototypeRequirement(workerName, amount);

			REQUIRE(package.workerData.requiredWorkers.count(prototypeId) > 0);
			REQUIRE(originalAmount + amount == package.workerData.requiredWorkers.at(prototypeId));
		}

		TEST_CASE("getRequiredWorkerCount where current data exists returns it", "[Services][WorkerRecruitmentService]")
		{
			Package package{};
			const std::string workerName = "Builder";
			const WorkerPrototypeId prototypeId = 231;
			const int originalAmount = 22;
			package.workerData.requiredWorkers[prototypeId] = originalAmount;

			fakeit::When(
				Method(
					package.workerPrototypeServiceMock,
					getPrototypeId
				)
			).Return(prototypeId);

			REQUIRE(originalAmount == package.service.getRequiredWorkerCount(workerName));
		}

		TEST_CASE("getRequiredWorkerCount where current data does not exist returns default", "[Services][WorkerRecruitmentService]")
		{
			Package package{};
			const std::string workerName = "Builder";
			const WorkerPrototypeId prototypeId = 231;

			fakeit::When(
				Method(
					package.workerPrototypeServiceMock,
					getPrototypeId
				)
			).Return(prototypeId);

			REQUIRE(0 == package.service.getRequiredWorkerCount(workerName));
		}

		TEST_CASE("reduceWorkerPrototypeRequirement where insufficient amount exists does nothing", "[Services][WorkerRecruitmentService]")
		{
			Package package{};
			const std::string workerName = "Builder";
			const WorkerPrototypeId prototypeId = 231;
			const int amount = 22;

			fakeit::When(
				Method(
					package.workerPrototypeServiceMock,
					getPrototypeId
				)
			).Return(prototypeId).Return(prototypeId);

			package.service.reduceWorkerPrototypeRequirement(workerName, amount);

			REQUIRE(0 == package.service.getRequiredWorkerCount(workerName));
		}

		TEST_CASE("reduceWorkerPrototypeRequirement where current data exists reduces it", "[Services][WorkerRecruitmentService]")
		{
			Package package{};
			const std::string workerName = "Builder";
			const WorkerPrototypeId prototypeId = 231;
			const int originalAmount = 22;
			const int amount = 21;
			package.workerData.requiredWorkers[prototypeId] = originalAmount;

			fakeit::When(
				Method(
					package.workerPrototypeServiceMock,
					getPrototypeId
				)
			).Return(prototypeId);

			package.service.reduceWorkerPrototypeRequirement(workerName, amount);

			REQUIRE(package.workerData.requiredWorkers.count(prototypeId) > 0);
			REQUIRE(originalAmount - amount == package.workerData.requiredWorkers.at(prototypeId));
		}

		TEST_CASE("getRequiredWorkerTypes returns list of required worker prototype ids", "[Services][WorkerRecruitmentService]")
		{
			Package package{};
			package.workerData.requiredWorkers[1] = 0;
			package.workerData.requiredWorkers[2] = 1;
			package.workerData.requiredWorkers[5] = 4;

			const auto& required = package.service.getRequiredWorkerTypes();

			REQUIRE(required.count(1) == 0);
			REQUIRE(required.count(2) > 0);
			REQUIRE(required.count(5) > 0);
		}

	}
}