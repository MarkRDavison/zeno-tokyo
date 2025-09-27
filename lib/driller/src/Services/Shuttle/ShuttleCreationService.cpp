#include <tokyo/Driller/Services/Shuttle/ShuttleCreationService.hpp>

namespace drl
{

	ShuttleCreationService::ShuttleCreationService(
		ShuttleData& _shuttleData,
		const IShuttlePrototypeService& _shuttlePrototypeService
	) :
		m_ShuttleData(_shuttleData),
		m_ShuttlePrototypeService(_shuttlePrototypeService)
	{

	}

	bool ShuttleCreationService::createShuttle(ShuttlePrototypeId _id)
	{
		if (!m_ShuttlePrototypeService.isPrototypeRegistered(_id))
		{
			return false;
		}
		const auto& prototype = m_ShuttlePrototypeService.getPrototype(_id);

		m_ShuttleData.shuttles.emplace_back(m_ShuttlePrototypeService.createInstanceById(_id));

		return true;
	}
}