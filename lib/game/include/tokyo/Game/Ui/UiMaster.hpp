#pragma once

#include <tokyo/Game/Ui/UiContainer.hpp>

namespace tokyo
{
	class UiMaster
	{
	public:
		static UiMaster* Get();

		void init(int screenWidth, int screenHeight, float manualSize);
		void enableMouseInteraction(bool enable);
		bool isMouseEnabled() const;

		void setMinDisplaySize(int width, int height);
		UiContainer* getContainer();
		float getUiSize() const;
		int getDisplayWidth() const;
		int getDisplayHeight() const;
		float getDisplayAspectRatio() const;
		bool isMouseInUi();
		void update(float delta);
		void notifyScreenSizeChange(int width, int height);
		void setManualUiSize(float size);
		void cleanup();
		void adjustUiSize();
		void checkDisplaySizeChange();
		void draw(sf::RenderTarget& target, sf::RenderStates states);

	private:
		static UiMaster* _instance;
		UiContainer* _container{ nullptr };
		int _displayWidthPixels;
		int _displayHeightPixels;
		float _displayAspect;
		bool _displaySizeUpdated{ false };
		bool _mouseInteractionEnabled{ true };

		int _minWidth;
		int _minHeight;

		float _manualUiSize{ 1.0f };
		float _uiSizeFactor{ 1.0f };
	};
}