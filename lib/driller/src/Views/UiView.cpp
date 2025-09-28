#include <tokyo/Driller/Views/UiView.hpp>
#include <iostream>

namespace drl
{

	UiView::UiView(
		IGameCommandService& _gameCommandService,
		const tokyo::FontManager& _fontManager,
		const tokyo::TextureManager& _textureManager,
		const tokyo::IInputActionManager& _inputActionManager,
		const tokyo::IResourceService& _resourceService,
		const ITerrainAlterationService& _terrainAlterationService,
		IUiService& _uiService
	) :
		m_GameCommandService(_gameCommandService),
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_InputActionManager(_inputActionManager),
		m_ResourceService(_resourceService),
		m_TerrainAlterationService(_terrainAlterationService),
		m_UiService(_uiService)
	{

	}

	void UiView::update(float _delta)
	{
		const auto size = sf::Vector2i(m_InputActionManager.getWindowSize());

		m_UiService.update(_delta);

		if (m_InputActionManager.isActionInvoked(drl::Constants::ClickActionName))
		{
			const auto mousePos = m_InputActionManager.getMousePosition();
			const auto pos = sf::Vector2f(mousePos - size / 2) / 64.0f; // TODO: SCALE/CONFIG/ZOOM

			const float tileY = std::floor(pos.y);
			const float tileX = pos.x < 0.0f
				? std::floor(pos.x + 0.5f)
				: std::ceil(pos.x - 0.5f);

			std::cout << "Tile " << tileX << ", " << tileY << std::endl;

			const auto uiState = m_UiService.getCurrentState();

			if (uiState == UiState::PLACING_BUILDING)
			{
				if (tileX != 0 && tileY >= 0)
				{
					m_GameCommandService.executeGameCommand(
						GameCommand(
							GameCommand::CreateJobEvent(
								"Job_Build_Building", 
								m_UiService.getActiveBuildingType(), 
								sf::Vector2i((int)tileX, (int)tileY)),
							GameCommand::CommandContext::PlacingBuilding,
							GameCommand::CommandSource::Player));

					if (!m_InputActionManager.isKeyDown(sf::Keyboard::Key::LShift) && 
						!m_InputActionManager.isKeyDown(sf::Keyboard::Key::RShift))
					{
						m_UiService.clearActiveBuilding();
					}
				}
			}
			else
			{
				if (tileX == 0)
				{
					// TODO: Temp - immediatly digging, not creating an in progress job/animation
					m_GameCommandService.executeGameCommand(
						GameCommand(
							GameCommand::DigShaftEvent((int)tileY),
							GameCommand::CommandContext::DiggingShaft,
							GameCommand::CommandSource::Player)
					);
				}
				else if (tileY >= 0)
				{
					int startX = (int)tileX;
					if (m_InputActionManager.isKeyDown(sf::Keyboard::Key::LShift) ||
						m_InputActionManager.isKeyDown(sf::Keyboard::Key::RShift))
					{
						startX = tileX > 0 ? +1 : -1;
					}
					if (tileX > 0)
					{
						for (int x = startX; x <= tileX; x++)
						{
							if (!m_TerrainAlterationService.isTileDugOut((int)tileY, (int)x))
							{
								m_GameCommandService.executeGameCommand(GameCommand(
									GameCommand::CreateJobEvent("Job_Dig", {}, sf::Vector2i((int)x, (int)tileY)),
									GameCommand::CommandContext::CreatingJob,
									GameCommand::CommandSource::Player)
								);
							}
						}
					}
					else
					{
						for (int x = startX; x >= tileX; x--)
						{
							if (!m_TerrainAlterationService.isTileDugOut((int)tileY, (int)x))
							{
								m_GameCommandService.executeGameCommand(GameCommand(
									GameCommand::CreateJobEvent("Job_Dig", {}, sf::Vector2i((int)x, (int)tileY)),
									GameCommand::CommandContext::CreatingJob,
									GameCommand::CommandSource::Player)
								);
							}
						}
					}
				}
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
		_states.texture = &m_TextureManager.getTexture(Constants::TileSpriteSheetTextureName);

		_target.draw(moneyText, _states);
	}

}