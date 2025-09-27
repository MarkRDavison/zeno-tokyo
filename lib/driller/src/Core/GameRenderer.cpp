#include <tokyo/Driller/Core/GameRenderer.hpp>
#include <SFML/Graphics.hpp>

namespace drl
{
	constexpr float Size{ 64.0f };

	GameRenderer::GameRenderer(
		GameData& _gameData,
		IGameCommandService& _gameCommandService,
		tokyo::FontManager& _fontManager,
		tokyo::TextureManager& _textureManager,
		const tokyo::IInputActionManager& _inputActionManager,
		const tokyo::IResourceService& _resourceService,
		const IWorkerPrototypeService& _workerPrototypeService,
		const IShuttlePrototypeService& _shuttlePrototypeService,
		const IBuildingPrototypeService& _buildingPrototypeService,
		const IJobPrototypeService& _jobPrototypeService,
		const ITerrainAlterationService& _terrainAlterationService,
		IUiService& _uiService
	) :
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_GameData(_gameData),
		m_TerrainView(_gameData.terrain, _textureManager),
		m_WorkerView(_gameData.worker, _workerPrototypeService, _textureManager),
		m_ShuttleView(_gameData.shuttle, _shuttlePrototypeService, _textureManager),
		m_BuildingView(_gameData.building, _buildingPrototypeService, _textureManager),
		m_JobView(_gameData.job, _jobPrototypeService, _textureManager),
		m_UiView(_gameData, _gameCommandService, _fontManager, _textureManager, _inputActionManager, _resourceService, _terrainAlterationService, _uiService)
	{

	}

	void GameRenderer::update(float _delta)
	{
		m_TerrainView.update(_delta);
		m_WorkerView.update(_delta);
		m_BuildingView.update(_delta);
		m_ShuttleView.update(_delta);
		m_JobView.update(_delta);
		m_UiView.update(_delta);
	}

	void GameRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		{
			sf::View view = target.getDefaultView();

			// TODO: Camera/view system seeded by config view scale? Or not zooming...
			view.setSize(
				{	
					(float)target.getSize().x / 64.0f/*m_ConfigurationManager.getGameViewScale()*/,
					-(float)target.getSize().y / 64.0f/*m_ConfigurationManager.getGameViewScale()*/
				}
			);

			view.setCenter({});

			target.setView(view);
		}

		{
			sf::VertexArray background(sf::PrimitiveType::Triangles);

			background.append(sf::Vertex({ -Size, +0.0f }, sf::Color::Cyan));
			background.append(sf::Vertex({ +Size, +0.0f }, sf::Color::Cyan));
			background.append(sf::Vertex({ +0.0f, +Size }, sf::Color::Cyan));
			background.append(sf::Vertex({ +Size, +0.0f }, sf::Color(128, 96, 77)));
			background.append(sf::Vertex({ -Size, +0.0f }, sf::Color(128, 96, 77)));
			background.append(sf::Vertex({ +0.0f, -Size }, sf::Color(128, 96, 77)));

			target.draw(background, states);
		}

		target.draw(m_TerrainView, states);
		target.draw(m_ShuttleView, states);
		target.draw(m_BuildingView, states);
		target.draw(m_WorkerView, states);
		target.draw(m_JobView, states);

		{
			sf::View view = target.getDefaultView();

			view.setSize(sf::Vector2f(target.getSize()));

			view.setCenter(sf::Vector2f(target.getSize()) / 2.0f);

			target.setView(view);
		}

		target.draw(m_UiView, states);
	}

}