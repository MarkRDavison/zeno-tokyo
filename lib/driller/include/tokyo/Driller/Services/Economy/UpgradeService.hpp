#pragma once

#include <tokyo/Driller/Entities/Data/UpgradeData.hpp>

namespace drl
{

	class IUpgradeService
	{
	public:
		virtual ~IUpgradeService(void) = 0;

		virtual void addUpgrade(IdType _upgradeType, float _value) = 0;
	};

	inline IUpgradeService::~IUpgradeService(void) = default;

	class UpgradeService : public IUpgradeService
	{
	public:
		UpgradeService(UpgradeData& _upgradeData);
		~UpgradeService() override = default;

		void addUpgrade(IdType _upgradeType, float _value) override;

	private:
		UpgradeData& m_UpgradeData;
	};

}