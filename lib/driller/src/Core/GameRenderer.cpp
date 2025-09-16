#include <tokyo/Driller/Core/GameRenderer.hpp>
#include <SFML/Graphics.hpp>

namespace drl
{
	constexpr float Size{ 64.0f };

	GameRenderer::GameRenderer(
		GameData& _gameData,
		tokyo::TextureManager& _textureManager,
		const WorkerPrototypeService& _workerPrototypeService,
		const ShuttlePrototypeService& _shuttlePrototypeService
	) :
		m_TextureManager(_textureManager),
		m_GameData(_gameData),
		m_WorkerPrototypeService(_workerPrototypeService),
		m_TerrainView(_gameData.terrain, _textureManager),
		m_WorkerView(_gameData.worker, _workerPrototypeService, _textureManager),
		m_ShuttleView(_gameData.shuttle, _shuttlePrototypeService, _textureManager)
	{

	}

	void GameRenderer::update(float _delta)
	{
		m_TerrainView.update(_delta);
		m_WorkerView.update(_delta);
		m_ShuttleView.update(_delta);
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
		target.draw(m_WorkerView, states);
	}

}