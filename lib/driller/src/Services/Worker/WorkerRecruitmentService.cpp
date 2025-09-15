#include <tokyo/Driller/Services/Worker/WorkerRecruitmentService.hpp>

namespace drl
{

	WorkerRecruitmentService::WorkerRecruitmentService(
		WorkerData& _workerData,
		const IWorkerPrototypeService& _workerPrototypeService
	) :
		m_WorkerData(_workerData),
		m_WorkerPrototypeService(_workerPrototypeService)
	{

	}

	void WorkerRecruitmentService::reduceWorkerPrototypeRequirement(const std::string& _prototypeName, int _amount)
	{
		reduceWorkerPrototypeRequirement(m_WorkerPrototypeService.getPrototypeId(_prototypeName), _amount);
	}
	void WorkerRecruitmentService::reduceWorkerPrototypeRequirement(WorkerPrototypeId _id, int _amount)
	{
		const auto existing = getRequiredWorkerCount(_id);
		if (existing >= _amount)
		{
			m_WorkerData.requiredWorkers[_id] -= _amount;
		}
	}
	void WorkerRecruitmentService::registerWorkerPrototypeRequirement(const std::string& _prototypeName, int _amount)
	{
		registerWorkerPrototypeRequirement(m_WorkerPrototypeService.getPrototypeId(_prototypeName), _amount);
	}
	void WorkerRecruitmentService::registerWorkerPrototypeRequirement(WorkerPrototypeId _id, int _amount)
	{
		m_WorkerData.requiredWorkers[_id] += _amount;
	}
	int WorkerRecruitmentService::getRequiredWorkerCount(const std::string& _prototypeName) const
	{
		return getRequiredWorkerCount(m_WorkerPrototypeService.getPrototypeId(_prototypeName));
	}
	int WorkerRecruitmentService::getRequiredWorkerCount(WorkerPrototypeId _id) const
	{
		if (m_WorkerData.requiredWorkers.count(_id) == 0)
		{
			return 0;
		}
		return m_WorkerData.requiredWorkers.at(_id);
	}
	std::unordered_set<WorkerPrototypeId> WorkerRecruitmentService::getRequiredWorkerTypes() const
	{
		std::unordered_set<WorkerPrototypeId> types;
		for (const auto& [k, v] : m_WorkerData.requiredWorkers)
		{
			if (v > 0)
			{
				types.insert(k);
			}
		}
		return types;
	}

}