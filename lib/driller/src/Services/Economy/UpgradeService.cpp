#include <tokyo/Driller/Services/Economy/UpgradeService.hpp>
#include <tokyo/Core/Utils/String.hpp>
#include <iostream>

namespace drl
{
	UpgradeService::UpgradeService(
		UpgradeData& _upgradeData
	) :
		m_UpgradeData(_upgradeData)
	{

	}

	void UpgradeService::addUpgrade(IdType _upgradeType, float _value)
	{
		// TODO: Should the value come from the event or from another upgrade?
		// TODO: Need to not have magic string here, should I have another entity, 'Upgrade'?
		if (_upgradeType == tokyo::String::fnv1a_32("Upgrade_Refine"))
		{
			m_UpgradeData.OreMultiplier += _value;
			std::cout << "Ore multiplier: " << m_UpgradeData.OreMultiplier << std::endl;
		}
	}
}