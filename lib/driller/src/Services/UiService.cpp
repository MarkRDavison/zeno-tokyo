#include <tokyo/Driller/Services/UiService.hpp>
#include <iostream>

namespace drl
{

	UiService::UiService(
		tokyo::IInputActionManager& _inputActionManager,
		IBuildingPrototypeService& _buildingPrototypeService
	) :
		m_InputActionManager(_inputActionManager),
		m_BuildingPrototypeService(_buildingPrototypeService)
	{

	}
	void UiService::update(float _delta)
	{
		if (m_InputActionManager.isActionInvoked(drl::Constants::CancelActionName))
		{
			if (!m_ActiveBuilding.empty())
			{
				m_ActiveBuilding.clear();
				m_CurrentUiState = UiState::DEFAULT;
				// m_InputActionManager.markAsHandled(drl::Constants::CancelActionName);
			}
		}
		else
		{
			int offset = 0;
			for (const auto& p : m_BuildingPrototypeService.getPrototypes())
			{
				if (m_InputActionManager.isKeyDown((sf::Keyboard::Key)(offset + (int)sf::Keyboard::Key::Num1)))
				{
					m_CurrentUiState = UiState::PLACING_BUILDING;
					m_ActiveBuilding = p.name;
					std::cout << "Active building set to: " << m_ActiveBuilding << std::endl;
					break;
				}
				offset++;
				if (offset >= 9)
				{
					break;
				}
			}
		}
	}

	std::string UiService::getActiveBuildingType() const
	{
		return m_ActiveBuilding;
	}

	UiState UiService::getCurrentState() const
	{
		return m_CurrentUiState;
	}

	void UiService::clearActiveBuilding()
	{
		m_ActiveBuilding = "";
		m_CurrentUiState = UiState::DEFAULT;
	}

}