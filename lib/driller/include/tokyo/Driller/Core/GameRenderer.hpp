#pragma once

#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Driller/Services/GameCommandService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttlePrototypeService.hpp>
#include <tokyo/Driller/Views/TerrainView.hpp>
#include <tokyo/Driller/Views/WorkerView.hpp>
#include <tokyo/Driller/Views/ShuttleView.hpp>
#include <tokyo/Driller/Views/BuildingView.hpp>
#include <tokyo/Driller/Views/JobView.hpp>
#include <tokyo/Driller/Views/UiView.hpp>
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
			IUiService& _uiService);

		void update(float _delta);
		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		tokyo::FontManager& m_FontManager;
		tokyo::TextureManager& m_TextureManager;
		GameData& m_GameData;
		TerrainView m_TerrainView;
		WorkerView m_WorkerView;
		ShuttleView m_ShuttleView;
		BuildingView m_BuildingView;
		JobView m_JobView;
		UiView m_UiView;
	};

}