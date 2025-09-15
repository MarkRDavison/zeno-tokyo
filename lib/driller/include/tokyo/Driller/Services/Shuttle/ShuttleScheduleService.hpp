#pragma once

#include <tokyo/Driller/Entities/Data/ShuttleData.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttleScheduleService.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttlePrototypeService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerRecruitmentService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerCreationService.hpp>

namespace drl
{

	class IShuttleScheduleService
	{
	public:
		virtual ~IShuttleScheduleService(void) = 0;

		virtual void update(float _delta) = 0;
	};

	inline IShuttleScheduleService::~IShuttleScheduleService(void) = default;

	class ShuttleScheduleService : public IShuttleScheduleService
	{
	public:
		ShuttleScheduleService(
			ShuttleData& _shuttleData,
			IWorkerRecruitmentService& _workerRecruitmentService,
			IWorkerCreationService& _workerCreationService,
			const IShuttlePrototypeService& _shuttlePrototypeService
		);
		~ShuttleScheduleService(void) override = default;

		void update(float _delta) override;
		void updateShuttle(float _delta, ShuttleInstance& _shuttle, const ShuttlePrototype& _prototype);
		bool moveShuttleTowardsLocation(float _delta, ShuttleInstance& _shuttle, const ShuttlePrototype& _prototype, sf::Vector2f _target, ShuttleState _nextState);

	private:
		ShuttleData& m_ShuttleData;
		IWorkerRecruitmentService& m_WorkerRecruitmentService;
		IWorkerCreationService& m_WorkerCreationService;
		const IShuttlePrototypeService& m_ShuttlePrototypeService;
	};

}