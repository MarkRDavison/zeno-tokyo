#pragma once

#include <tokyo/Core/Infrastructure/FontManager.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Game/InputActionManager.hpp>
#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Driller/Services/GameCommandService.hpp>
#include <tokyo/Driller/Services/UiService.hpp>
#include <tokyo/Driller/Views/View.hpp>

namespace drl
{

	class UiView : public View
	{
	public:
		UiView(
			const GameData& _gameData,
			IGameCommandService& _gameCommandService,
			const tokyo::FontManager& _fontManager,
			const tokyo::TextureManager& _textureManager,
			const tokyo::IInputActionManager& _inputActionManager,
			const tokyo::IResourceService& _resourceService,
			const ITerrainAlterationService& _terrainAlterationService,
			IUiService& _uiService
		);
		~UiView(void) override = default;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:
		const GameData& m_GameData;
		IGameCommandService& m_GameCommandService;
		const tokyo::FontManager& m_FontManager;
		const tokyo::TextureManager& m_TextureManager;
		const tokyo::IInputActionManager& m_InputActionManager;
		const tokyo::IResourceService& m_ResourceService;
		const ITerrainAlterationService& m_TerrainAlterationService;
		IUiService& m_UiService;
	};

}