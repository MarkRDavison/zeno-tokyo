#pragma once

#include <tokyo/Game/Entity/PrototypeService.hpp>
#include <tokyo/Game/Entity/IdentityService.hpp>
#include <tokyo/Driller/Entities/Job.hpp>

namespace drl
{
	using IJobPrototypeService = tokyo::IPrototypeService<JobPrototype, JobInstance, JobPrototypeId>;

	class JobPrototypeService : public tokyo::PrototypeService<JobPrototype, JobInstance, JobPrototypeId>
	{
	public:
		JobPrototypeService(tokyo::IIdentificationService<IdType>& _identificationService);
		~JobPrototypeService(void) override = default;

		JobInstance createInstance(const JobPrototype& _prototype) const override;
	};

}