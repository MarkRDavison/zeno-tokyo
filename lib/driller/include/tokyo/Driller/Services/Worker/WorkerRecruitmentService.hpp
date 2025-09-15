#pragma once

#include <tokyo/Driller/Entities/Data/WorkerData.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>
#include <unordered_set>

namespace drl
{

	class IWorkerRecruitmentService
	{
	public:
		virtual ~IWorkerRecruitmentService(void) = 0;

		virtual void reduceWorkerPrototypeRequirement(const std::string& _prototypeName, int _amount) = 0;
		virtual void reduceWorkerPrototypeRequirement(WorkerPrototypeId _id, int _amount) = 0;
		virtual void registerWorkerPrototypeRequirement(const std::string& _prototypeName, int _amount) = 0;
		virtual void registerWorkerPrototypeRequirement(WorkerPrototypeId _id, int _amount) = 0;
		virtual int getRequiredWorkerCount(const std::string& _prototypeName) const = 0;
		virtual int getRequiredWorkerCount(WorkerPrototypeId _id) const = 0;
		virtual std::unordered_set<WorkerPrototypeId> getRequiredWorkerTypes() const = 0;
	};

	inline IWorkerRecruitmentService::~IWorkerRecruitmentService(void) = default;

	class WorkerRecruitmentService : public IWorkerRecruitmentService
	{
	public:
		WorkerRecruitmentService(
			WorkerData& _workerData,
			const IWorkerPrototypeService& _workerPrototypeService
		);
		~WorkerRecruitmentService(void) override = default;

		void reduceWorkerPrototypeRequirement(const std::string& _prototypeName, int _amount) override;
		void reduceWorkerPrototypeRequirement(WorkerPrototypeId _id, int _amount) override;
		void registerWorkerPrototypeRequirement(const std::string& _prototypeName, int _amount) override;
		void registerWorkerPrototypeRequirement(WorkerPrototypeId _id, int _amount) override;
		int getRequiredWorkerCount(const std::string& _prototypeName) const override;
		int getRequiredWorkerCount(WorkerPrototypeId _id) const override;
		std::unordered_set<WorkerPrototypeId> getRequiredWorkerTypes() const override;

	private:
		WorkerData& m_WorkerData;
		const IWorkerPrototypeService& m_WorkerPrototypeService;
	};

}