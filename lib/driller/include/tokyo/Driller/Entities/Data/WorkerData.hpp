#pragma once

#include <tokyo/Driller/Entities/Worker.hpp>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <vector>

namespace drl
{

	struct WorkerData
	{
		std::vector<WorkerInstance> workers;
		std::unordered_map<WorkerPrototypeId, int> requiredWorkers;

		WorkerInstance& getWorker(WorkerId _workerId)
		{
			const auto& WorkerIter = std::find_if(workers.begin(), workers.end(),
				[_workerId](const WorkerInstance& _j) -> bool
				{
					return _j.Id == _workerId;
				}
			);

			if (WorkerIter == workers.end())
			{
				throw std::logic_error("Invalid worker id");
			}

			return *WorkerIter;
		}
		const WorkerInstance& getWorker(WorkerId _workerId) const
		{
			const auto& WorkerIter = std::find_if(workers.begin(), workers.end(),
				[_workerId](const WorkerInstance& _j) -> bool
				{
					return _j.Id == _workerId;
				}
			);

			if (WorkerIter == workers.end())
			{
				throw std::logic_error("Invalid worker id");
			}

			return *WorkerIter;
		}
	};

}