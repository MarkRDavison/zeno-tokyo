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
		const auto size = sf::Vector2i(m_InputActionManager.getWindowSize());

		if (m_InputActionManager.isActionInvoked(drl::Constants::ClickActionName))
		{
			const auto mousePos = m_InputActionManager.getMousePosition();
			const auto pos = sf::Vector2f(m_InputActionManager.getMousePosition() - size / 2) / 64.0f; // TODO: SCALE/CONFIG

			const float tileY = std::floor(pos.y);
			const float tileX = pos.x < 0.0f
				? std::floor(pos.x + 0.5f)
				: std::ceil(pos.x - 0.5f);

			std::cout << "Tile " << tileX << ", " << tileY << std::endl;

			// if (building building)
			{

			}
			if (tileX == 0)
			{
				m_GameCommandService.executeGameCommand(
					// TODO: Temp - immediatly digging, not creating an in progress job/animation
					GameCommand(GameCommand::DigShaftEvent((int)tileY), GameCommand::CommandContext::DiggingShaft, GameCommand::CommandSource::Player)
				);
			}
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