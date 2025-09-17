#include <tokyo/Driller/Services/Job/JobCreationService.hpp>

namespace drl
{

	JobCreationService::JobCreationService(
		JobData& _jobData,
		const IJobPrototypeService& _jobPrototypeService,
		ITerrainAlterationService& _terrainAlterationService
	) :
		m_JobData(_jobData),
		m_JobPrototypeService(_jobPrototypeService),
		m_TerrainAlterationService(_terrainAlterationService)
	{

	}

	bool JobCreationService::createJob(JobPrototypeId _id, JobPrototypeId _additionalPrototypeId, sf::Vector2i _coordinates)
	{;
		if (!m_JobPrototypeService.isPrototypeRegistered(_id))
		{
			return false;
		}
		const auto& prototype = m_JobPrototypeService.getPrototype(_id);

		auto& tile = m_TerrainAlterationService.getTile(_coordinates.y, _coordinates.x);
		if (tile.jobReserved)
		{
			return false;
		}

		auto& job = m_JobData.jobs.emplace_back(m_JobPrototypeService.createInstanceById(_id));
		job.additionalPrototypeId = _additionalPrototypeId;
		job.tile = _coordinates;
		tile.jobReserved = true;

		// TODO: Should this not just be a generic function that does more than calc offsets?, pass in ref to job instance?
		if (prototype.calculateOffset)
		{
			job.offset = prototype.calculateOffset(job, prototype);
		}

		return true;
	}

	bool JobCreationService::createJob(const std::string& _jobPrototypeName, sf::Vector2f _offset, sf::Vector2i _coordinates)
	{
		const auto id = m_JobPrototypeService.getPrototypeId(_jobPrototypeName);
		if (!m_JobPrototypeService.isPrototypeRegistered(id))
		{
			return false;
		}
		const auto& prototype = m_JobPrototypeService.getPrototype(id);

		auto& job = m_JobData.jobs.emplace_back(m_JobPrototypeService.createInstanceById(id));
		job.additionalPrototypeId = 0;
		job.tile = _coordinates;
		job.offset = _offset;

		return true;
	}

}