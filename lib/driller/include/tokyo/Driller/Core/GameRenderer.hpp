#pragma once

#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>
#include <tokyo/Driller/Views/TerrainView.hpp>
#include <tokyo/Driller/Views/WorkerView.hpp>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace drl
{
	class GameRenderer : public tokyo::NonCopyable, public sf::Drawable
	{
	public:
		GameRenderer(
			GameData& _gameData,
			tokyo::TextureManager& _textureManager,
			const WorkerPrototypeService& _workerPrototypeService);

		void update(float _delta);
		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		tokyo::TextureManager& m_TextureManager;
		GameData& m_GameData;
		TerrainView m_TerrainView;
		WorkerView m_WorkerView;
		const WorkerPrototypeService& m_WorkerPrototypeService;
	};

}