#include <tokyo/Driller/Views/UiView.hpp>
#include <iostream>

namespace drl
{

	UiView::UiView(
		const GameData& _gameData,
		IGameCommandService& _gameCommandService,
		const tokyo::FontManager& _fontManager,
		const tokyo::TextureManager& _textureManager,
		const tokyo::IInputActionManager& _inputActionManager,
		const tokyo::IResourceService& _resourceService
	) :
		m_GameData(_gameData),
		m_GameCommandService(_gameCommandService),
		m_FontManager(_fontManager),
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
			std::cout << "|" << std::endl;
			std::cout << "| Ore: \t\t" << ore.resource.amount << std::endl;
			std::cout << "| Money: \t" << money.resource.amount << std::endl;
			std::cout << "|" << std::endl;
			std::cout << "=============================================" << std::endl << std::endl;
		}
	}

	void UiView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
	{
		auto& font = m_FontManager.getFont("DEBUG");
		const auto& ore = m_ResourceService.getExistingResource("Resource_Ore");
		sf::Text oreText(font, "Ore: " + std::to_string(ore.resource.amount));
		oreText.setFillColor(sf::Color::Black);
		const auto& money = m_ResourceService.getExistingResource("Resource_Money");
		sf::Text moneyText(font, "Money: " + std::to_string(money.resource.amount));
		moneyText.setFillColor(sf::Color::Black);

		_states.transform.translate({ 4.0f, 0.0f });
		_target.draw(oreText, _states);
		_states.transform.translate({ 0.0f, 32.0f });
		_target.draw(moneyText, _states);
	}

}