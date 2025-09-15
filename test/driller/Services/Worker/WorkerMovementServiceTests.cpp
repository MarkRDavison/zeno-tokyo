#include <catch2/catch_test_macros.hpp>
#include <tokyo/Driller/Services/Worker/WorkerMovementService.hpp>
#include <SFML/System/Vector2.hpp>
#include <fakeit.hpp>

namespace drl
{
    namespace WorkerMovementServiceTests
    {
        struct Package {
            Package() :
                service(
                    workerData,
                    jobData,
                    terrainAlterationServiceMock.get()
                ) 
            {
            }

            WorkerData workerData;
            JobData jobData;

            fakeit::Mock<ITerrainAlterationService> terrainAlterationServiceMock;

            WorkerMovementService service;
        };

        TEST_CASE("updateWorker idle worker with assigned job id updates it", "[Services][WorkerMovementService]") {
            Package package{};

            auto& j = package.jobData.jobs.emplace_back();
            auto& w = package.workerData.workers.emplace_back();
            j.Id = 1;
            w.Id = 22;
            w.allocatedJobId = j.Id;
            j.allocatedWorkerId = w.Id;
            j.tile = { 2,0 };
            w.position = { 0.0f, 1.0f };

            package.service.updateWorker(0.0f, w);

            REQUIRE(WorkerState::MovingToJob == w.state);
        }

        TEST_CASE("updateWorker moving to job worker moves it towards its job location", "[Services][WorkerMovementService]") {
            Package package{};

            auto& j = package.jobData.jobs.emplace_back();
            auto& w = package.workerData.workers.emplace_back();
            j.Id = 1;
            w.Id = 22;
            w.allocatedJobId = j.Id;
            j.allocatedWorkerId = w.Id;
            j.tile = { 2,0 };
            w.position = { 0.0f, 1.0f };

            const float delta = 1.0f;

            package.service.updateWorker(delta, w);

            REQUIRE(WorkerState::MovingToJob == w.state);
            REQUIRE(sf::Vector2f(delta, 1.0f) == w.position);

            package.service.updateWorker(delta, w);

            REQUIRE(WorkerState::WorkingJob == w.state);
            REQUIRE(sf::Vector2f(delta * 2.0f, 1.0f) == w.position);
        }
    }
}