#pragma once

#include <tokyo/Driller/Entities/Data/JobData.hpp>
#include <tokyo/Driller/Services/Job/JobPrototypeService.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>

namespace drl
{

	class IJobCreationService
	{
	public:
		virtual ~IJobCreationService(void) = 0;

		virtual bool createJob(JobPrototypeId _id, JobPrototypeId _additionalPrototypeId, sf::Vector2i _coordinates) = 0;
		virtual bool createJob(const std::string& _jobPrototypeName, sf::Vector2f _offset, sf::Vector2i _coordinates) = 0;
	};

	inline IJobCreationService::~IJobCreationService(void) = default;

	class JobCreationService : public IJobCreationService
	{
	public:
		JobCreationService(
			JobData& _jobData,
			const IJobPrototypeService& _jobPrototypeService,
			ITerrainAlterationService& _terrainAlterationService
		);
		~JobCreationService(void) override = default;

		bool createJob(JobPrototypeId _id, JobPrototypeId _additionalPrototypeId, sf::Vector2i _coordinates) override;
		bool createJob(const std::string& _jobPrototypeName, sf::Vector2f _offset, sf::Vector2i _coordinates) override;

	private:
		JobData& m_JobData;
		const IJobPrototypeService& m_JobPrototypeService;
		ITerrainAlterationService& m_TerrainAlterationService;
	};

}