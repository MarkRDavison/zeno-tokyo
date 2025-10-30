#include <tokyo/Game/Ui/UiComponent.hpp>
#include <tokyo/Game/Ui/UiConstraint.hpp>
#include <tokyo/Game/Ui/UiConstraints.hpp>
#include <tokyo/Game/Ui/UiMaster.hpp>

namespace tokyo
{
	void UiComponent::show(bool show)
	{
		_visible = show;
	}
	bool UiComponent::isShown() const
	{
		return _visible;
	}

	void UiComponent::add(UiComponent* component, UiConstraints* constraints)
	{
		component->_constraints = constraints;
		constraints->notifyAdded(component, this);
		component->_parent = this;
		if (_initialised)
		{
			initChild(component);
		}
		else
		{
			_childrenToAdd.push_back(component);
		}
	}
	void UiComponent::addInStyle(UiComponent* component, UiConstraints* constraints)
	{
		component->setHidden();
		add(component, constraints);
		component->display(true);
	}
	void UiComponent::removeInStyle()
	{
		this->remove();
		/*
		if (_displayTransition == nullptr)
		{
			this->remove();
		}
		else
		{
			_removeFlag = true;
			_component->display(false);
		}
		*/
	}
	void UiComponent::setHidden()
	{
		_displayed = false;
		show(false);
	}
	void UiComponent::setDisplayed()
	{
		_displayed = true;
		show(true);
	}
	void UiComponent::display(bool display)
	{
		if (display == _displayed)
		{
			return;
		}

		_displayed = display;

		if (display)
		{
			show(true);
		}
		// doDisplayAnimation(dsiplay, 0, true);
	}
	bool UiComponent::isDisplayed() const
	{
		return _displayed;
	}
	float UiComponent::getAbsX() const
	{
		return _x;
	}
	float UiComponent::getAbsY() const
	{
		return _y;
	}
	float UiComponent::getAbsWidth() const
	{
		return _width;
	}
	float UiComponent::getAbsHeight() const
	{
		return _height;
	}
	UiConstraint* UiComponent::getXConstraint() const
	{
		return _constraints->getX();
	}
	UiConstraint* UiComponent::getYConstraint() const
	{
		return _constraints->getY();
	}
	UiConstraint* UiComponent::getWidthConstraint() const
	{
		return _constraints->getWidth();
	}
	UiConstraint* UiComponent::getHeightConstraint() const
	{
		return _constraints->getHeight();
	}
	float UiComponent::pixelsToRelativeX(float pixels) const
	{
		return pixels / getPixelWidth();
	}
	float UiComponent::pixelsToRelativeY(float pixels) const
	{
		return pixels / getPixelHeight();
	}
	float UiComponent::getPixelWidth() const
	{
		return _width / UiMaster::Get()->getDisplayWidth();
	}
	float UiComponent::getPixelHeight() const
	{
		return _height / UiMaster::Get()->getDisplayHeight();
	}
	float UiComponent::getAbsAspectRatio() const
	{
		return getPixelWidth() / getPixelHeight();
	}
	float UiComponent::getRelativeWidthCoords(float relativeWidth) const
	{
		return relativeWidth * getAbsAspectRatio();
	}
	float UiComponent::getRelativeHeightCoords(float relativeHeight) const
	{
		return relativeHeight * getAbsAspectRatio();
	}
	bool UiComponent::isClickedOn(sf::Mouse::Button button)
	{
		// TODO: Is clicked event not is pressed
		return isMouseOver() && sf::Mouse::isButtonPressed(button);
	}
	sf::Vector2f UiComponent::getMouseRelativePosition() const
	{
		// TODO: Inject window????
		auto pos = sf::Mouse::getPosition();
		return sf::Vector2f((pos.x - _x) / _width, (pos.y - _y) / _height);
	}
	void UiComponent::setAlpha(float selfAlpha)
	{
		_selfAlpha = selfAlpha;
		if (_initialised)
		{
			updateTotalAlpha();
		}
	}
	float UiComponent::getSelfAlpha() const
	{
		return _selfAlpha;
	}
	void UiComponent::updateTotalAlpha()
	{
		calcTotalAlpha();
		for (auto child : _children)
		{
			child->updateTotalAlpha();
		}
	}
	void UiComponent::calcTotalAlpha()
	{
		auto animationAlpha = 1.0f; // _animator == nullptr ? 1.0f : _animator->getAlpha();
		_totalAlpha = _parent->_totalAlpha * _selfAlpha * animationAlpha;
	}
	void UiComponent::remove()
	{
		_parent->_childrenToRemove.push_back(this);
	}
	void UiComponent::removeOldComponents()
	{
		for (auto c : _childrenToRemove)
		{
			_children.erase(std::find(_children.begin(), _children.end(), c));
			c->deleteSelf();
		}

		_childrenToRemove.clear();
	}
	void UiComponent::forceInitialisation(float absX, float absY, float absWidth, float absHeight)
	{
		_x = absX;
		_y = absY;
		_width = absWidth;
		_height = absHeight;
		_initialised = true;
	}
	void UiComponent::deleteSelf()
	{
		for (auto c : _children)
		{
			c->deleteSelf();
		}
		for (auto c : _childrenToAdd)
		{
			c->deleteSelf();
		}
		for (auto c : _childrenToRemove)
		{
			c->deleteSelf();
		}
	}
	std::vector<UiComponent*>& UiComponent::getChildren()
	{
		return _children;
	}
	UiComponent* UiComponent::getParent() const
	{
		return _parent;
	}
	void UiComponent::update(float delta)
	{
		if (!_visible)
		{
			return;
		}

		updateSelf();
		//updateAnimation(delta);
		removeOldComponents();
		// getRenderData();
		for (auto c : _children)
		{
			c->update(delta);
		}
	}
	void UiComponent::replace(UiComponent* component)
	{
		remove();
		_parent->add(component, _constraints);
	}
	void UiComponent::calculateScreenSpacePosition(bool calcScale)
	{
		_x = _parent->_x + (_constraints->getX()->getRelativeValue() + _xModifier) /* * getAnimationX() */ * _parent->_width;
		_y = _parent->_y + (_constraints->getY()->getRelativeValue() + _yModifier) /* * getAnimationY() */ * _parent->_height;

		if (calcScale)
		{
			_width = _constraints->getWidth()->getRelativeValue() * _parent->_width * _widthModifier; // getAnimWidth();
			_height = _constraints->getHeight()->getRelativeValue() * _parent->_height * _heightModifier; // getAnimHeight();
		}
	}
	void UiComponent::clear()
	{
		_childrenToRemove.assign(_children.begin(), _children.end());
	}
	void UiComponent::clearInStyle()
	{
		for (auto c : _children)
		{
			c->removeInStyle();
		}
	}
	void UiComponent::notifyDimensionChange(bool scaleChange)
	{
		if (scaleChange && _reloadOnSizeChanged)
		{
			reload();
			return;
		}

		for (auto c : _children)
		{
			c->notifyDimensionChange(scaleChange);
		}
	}
	float UiComponent::absToRelativeX(float absX) const
	{
		return (absX - _x) / _width;
	}
	float UiComponent::absToRelativeY(float absY) const
	{
		return (absY - _y) / _height;
	}
	bool UiComponent::isMouseOver()
	{
		if (/*UiMaster.isMouseEnabled() &&*/!isShown())
		{
			return false;
		}

		auto pos = sf::Mouse::getPosition();
		if (pos.x >= _x && _x <= _x + _width)
		{
			if (pos.y >= _y && _y <= _y + _height)
			{
				return true;
			}
		}

		return false;
	}
	void UiComponent::setLevel(int level)
	{
		_level = level;
		for (auto c : _children)
		{
			if (level > c->_level)
			{
				c->setLevel(level);
			}
		}
	}
	int UiComponent::getLevel() const
	{
		return _level;
	}
	void UiComponent::reload()
	{
		clear();
		init();
	}
	void UiComponent::initChild(UiComponent* child)
	{
		_children.push_back(child);
		child->_level = std::max(_level, child->_level);
		child->calculateScreenSpacePosition(true);
		child->init();
		child->calcTotalAlpha();
		child->_initialised = true;
		child->initAllChildren();
	}
	void UiComponent::initAllChildren()
	{
		for (auto c : _childrenToAdd)
		{
			initChild(c);
		}

		_childrenToAdd.clear();
	}
}