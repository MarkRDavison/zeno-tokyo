#include <tokyo/Driller/Views/UiView.hpp>
#include <iostream>

namespace drl
{

	UiView::UiView(
		const GameData& _gameData,
		IGameCommandService& _gameCommandService,
		const tokyo::TextureManager& _textureManager,
		const tokyo::IInputActionManager& _inputActionManager,
		const tokyo::IResourceService& _resourceService
	) :
		m_GameData(_gameData),
		m_GameCommandService(_gameCommandService),
		m_TextureManager(_textureManager),
		m_InputActionManager(_inputActionManager),
		m_ResourceService(_resourceService)
	{

	}

	void UiView::update(float _delta)
	{
		if (m_InputActionManager.isActionInvoked(drl::Constants::ClickActionName))
		{
			const auto& ore = m_ResourceService.getExistingResource("Resource_Ore");
			const auto& money = m_ResourceService.getExistingResource("Resource_Money");

			std::cout << "================= Resources =================" << std::endl;
			std::cout << "| Ore: " << ore.resource.amount << std::endl;
			std::cout << "| Money: " << money.resource.amount << std::endl;
			std::cout << "=============================================" << std::endl << std::endl;
		}
	}
	void UiView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
	{

	}

}