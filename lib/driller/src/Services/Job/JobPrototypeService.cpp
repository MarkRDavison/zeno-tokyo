#include <tokyo/Driller/Services/Job/JobPrototypeService.hpp>

namespace drl
{

	JobPrototypeService::JobPrototypeService(
		tokyo::IIdentificationService<IdType>& _identificationService
	) :
		PrototypeService<JobPrototype, JobInstance, JobPrototypeId>(_identificationService)
	{

	}

	JobInstance JobPrototypeService::createInstance(const JobPrototype& _prototype) const
	{
		JobInstance job{};
		job.Id = m_IdentificationService.generateId();
		job.prototypeId = getPrototypeId(_prototype.name);
		job.work = _prototype.work;
		return job;
	}

}