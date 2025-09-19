#include <tokyo/Driller/Services/Economy/EconomyService.hpp>

namespace drl
{

	EconomyService::EconomyService() 
	{

	}

	tokyo::Resource EconomyService::getSaleResource(const tokyo::Resource& resourceToSell) const
	{
		return { "Resource_Money", resourceToSell.amount };
	}
}