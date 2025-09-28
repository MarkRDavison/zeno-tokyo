#pragma once

#include <tokyo/Driller/Entities/Job.hpp>
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace drl
{

	struct JobData
	{
		std::vector<JobInstance> jobs;

		JobInstance& getJob(JobId _jobId)
		{
			const auto& jobIter = std::find_if(jobs.begin(), jobs.end(),
				[_jobId](const JobInstance& _j) -> bool
				{
					return _j.Id == _jobId;
				}
			);

			if (jobIter == jobs.end())
			{
				throw std::logic_error("Invalid job id");
			}

			return *jobIter;
		}
		const JobInstance& getJob(JobId _jobId) const
		{
			const auto& jobIter = std::find_if(jobs.begin(), jobs.end(),
				[_jobId](const JobInstance& _j) -> bool
				{
					return _j.Id == _jobId;
				}
			);

			if (jobIter == jobs.end())
			{
				throw std::logic_error("Invalid job id");
			}

			return *jobIter;
		}
	};

}