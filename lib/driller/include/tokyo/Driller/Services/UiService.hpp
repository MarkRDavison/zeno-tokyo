#pragma once

#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Driller/Services/Building/BuildingPrototypeService.hpp>
#include <tokyo/Game/InputActionManager.hpp>

namespace drl
{

	enum class UiState
	{
		DEFAULT = 0,
		PLACING_BUILDING = 1
	};

	class IUiService
	{
	public:
		virtual ~IUiService() = 0;
		
		virtual void update(float _delta) = 0;

		virtual std::string getActiveBuildingType() const = 0;
		virtual UiState getCurrentState() const = 0;

		virtual void clearActiveBuilding() = 0;
	};

	inline IUiService::~IUiService() = default;

	class UiService : public IUiService
	{
	public:
		UiService(
			tokyo::IInputActionManager& _inputActionManager,
			IBuildingPrototypeService& _buildingPrototypeService
		);
		~UiService() override = default;

		void update(float _delta) override;

		std::string getActiveBuildingType() const override;

		UiState getCurrentState() const override;

		void clearActiveBuilding() override;

	private:
		tokyo::IInputActionManager& m_InputActionManager;
		IBuildingPrototypeService& m_BuildingPrototypeService;
		std::string m_ActiveBuilding;
		UiState m_CurrentUiState{ UiState::DEFAULT };
	};
}