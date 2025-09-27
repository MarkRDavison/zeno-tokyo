#pragma once

#include <tokyo/Driller/Entities/Data/ShuttleData.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttlePrototypeService.hpp>

namespace drl
{

	class IShuttleCreationService
	{
	public:
		virtual ~IShuttleCreationService(void) = 0;

		virtual bool createShuttle(ShuttlePrototypeId _id) = 0;
	};

	inline IShuttleCreationService::~IShuttleCreationService(void) = default;

	class ShuttleCreationService : public IShuttleCreationService
	{
	public:
		ShuttleCreationService(
			ShuttleData& _shuttleData,
			const IShuttlePrototypeService& _shuttlePrototypeService
		);
		~ShuttleCreationService(void) override = default;

		bool createShuttle(ShuttlePrototypeId _id) override;

	private:
		ShuttleData& m_ShuttleData;
		const IShuttlePrototypeService& m_ShuttlePrototypeService;
	};

}