#include <tokyo/Game/Ui/UiMaster.hpp>

namespace tokyo
{
	UiMaster* UiMaster::_instance{ nullptr };
	UiMaster* UiMaster::Get()
	{
		if (_instance == nullptr)
		{
			_instance = new UiMaster();
		}

		return _instance;
	}

	void UiMaster::init(int screenWidth, int screenHeight, float manualSize)
	{
		_displayWidthPixels = screenWidth;
		_displayHeightPixels = screenHeight;
		_manualUiSize = manualSize;
		_displayAspect = (float)(screenWidth) / (float)(screenHeight);
		adjustUiSize();
	}
	void UiMaster::enableMouseInteraction(bool enable)
	{
		_mouseInteractionEnabled = enable;
	}
	bool UiMaster::isMouseEnabled() const
	{
		return _mouseInteractionEnabled;
	}
	void UiMaster::setMinDisplaySize(int width, int height)
	{
		_minWidth = width;
		_minHeight = height;
	}
	UiContainer* UiMaster::getContainer()
	{
		if (_container == nullptr)
		{
			_container = new UiContainer();
		}

		return _container;
	}
	float UiMaster::getUiSize() const
	{
		return _uiSizeFactor;
	}
	int UiMaster::getDisplayWidth() const
	{
		return (int)(_displayWidthPixels / _uiSizeFactor);
	}
	int UiMaster::getDisplayHeight() const
	{
		return (int)(_displayHeightPixels / _uiSizeFactor);
	}
	float UiMaster::getDisplayAspectRatio() const
	{
		return _displayAspect;
	}
	bool UiMaster::isMouseInUi()
	{
		return getContainer()->isMouseOver();
	}
	void UiMaster::update(float delta)
	{
		checkDisplaySizeChange();
		getContainer()->update(delta);

		// TODO: RENDER
	}
	void UiMaster::notifyScreenSizeChange(int width, int height)
	{
		_displaySizeUpdated = true;
		_displayWidthPixels = width;
		_displayHeightPixels = height;
		_displayAspect = (float)(_displayWidthPixels) / (float)(_displayHeightPixels);
		adjustUiSize();
	}
	void UiMaster::setManualUiSize(float size)
	{
		_manualUiSize = size;
		_displaySizeUpdated = true;
		adjustUiSize();
	}
	void UiMaster::cleanup()
	{
		getContainer()->deleteSelf();
	}
	void UiMaster::adjustUiSize()
	{
		_uiSizeFactor = _manualUiSize;
		
		if (_displayWidthPixels < _minWidth * _manualUiSize)
		{
			_uiSizeFactor = (float)_displayWidthPixels / _minWidth;
		}

		if (_displayHeightPixels < _minHeight * _manualUiSize)
		{
			_uiSizeFactor = std::min((float)_displayHeightPixels / _minHeight, _uiSizeFactor);
		}
	}
	void UiMaster::checkDisplaySizeChange()
	{
		if (!_displaySizeUpdated)
		{
			return;
		}

		getContainer()->notifyDimensionChange(true);
		for (auto c : getContainer()->getChildren())
		{
			c->notifyDimensionChange(true);
		}

		_displaySizeUpdated = false;
	}

	void UiMaster::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		getContainer()->draw(target, states);
		for (const auto& c : getContainer()->getChildren())
		{
			c->draw(target, states);
		}
	}
}