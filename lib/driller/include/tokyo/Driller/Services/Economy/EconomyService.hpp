#pragma once

#include <tokyo/Game/Resource/Resource.hpp>

namespace drl 
{

	class IEconomyService
	{
	public:
		virtual ~IEconomyService(void) = 0;

		virtual tokyo::Resource getSaleResource(const tokyo::Resource& resourceToSell) const = 0;
	};

	inline IEconomyService::~IEconomyService(void) = default;

	class EconomyService : public IEconomyService
	{
	public:
		EconomyService();
		~EconomyService() override = default;

		tokyo::Resource getSaleResource(const tokyo::Resource& resourceToSell) const override;
	};

}