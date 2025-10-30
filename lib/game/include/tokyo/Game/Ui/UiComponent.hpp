#pragma once

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

namespace tokyo
{
	class UiConstraint;
	class UiConstraints;
	class UiComponent
	{
	public:
		void show(bool show);
		bool isShown() const;

		void add(UiComponent* component, UiConstraints* constraints);
		void addInStyle(UiComponent* component, UiConstraints* constraints);
		void removeInStyle();
		void setHidden();
		void setDisplayed();
		void display(bool display);
		bool isDisplayed() const;
		// addText
		float getAbsX() const;
		float getAbsY() const;
		float getAbsWidth() const;
		float getAbsHeight() const;
		UiConstraint* getXConstraint() const;
		UiConstraint* getYConstraint() const;
		UiConstraint* getWidthConstraint() const;
		UiConstraint* getHeightConstraint() const;
		float pixelsToRelativeX(float pixels) const;
		float pixelsToRelativeY(float pixels) const;
		float getPixelWidth() const;
		float getPixelHeight() const;
		float getAbsAspectRatio() const;
		float getRelativeWidthCoords(float relativeWidth) const;
		float getRelativeHeightCoords(float relativeHeight) const;
		bool isClickedOn(sf::Mouse::Button button);
		sf::Vector2f getMouseRelativePosition() const;
		void setAlpha(float selfAlpha);
		float getSelfAlpha() const;
		void updateTotalAlpha();
		void calcTotalAlpha();
		void remove();
		void removeOldComponents();
		void forceInitialisation(float absX, float absY, float absWidth, float absHeight);
		virtual void init() = 0;
		void deleteSelf();
		std::vector<UiComponent*>& getChildren();
		UiComponent* getParent() const;
		void update(float delta);
		void replace(UiComponent* component);
		void calculateScreenSpacePosition(bool calcScale);
		virtual void updateSelf(void) = 0;
		void clear();
		void clearInStyle();
		void notifyDimensionChange(bool scaleChange);
		float absToRelativeX(float absX) const;
		float absToRelativeY(float absY) const;
		virtual bool isMouseOver();
		void setLevel(int level);
		int getLevel() const;
		void reload();
		void initChild(UiComponent* child);
		void initAllChildren();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const
		{

		}


	private:
		bool _visible{ true };
		std::vector<UiComponent*> _children;
		std::vector<UiComponent*> _childrenToAdd;
		std::vector<UiComponent*> _childrenToRemove;
		UiComponent* _parent{ nullptr };
		UiConstraints* _constraints{ nullptr };
		float _xModifier{ 0.0f };
		float _yModifier{ 0.0f };
		float _widthModifier{ 0.0f };
		float _heightModifier{ 0.0f };
		// Animator _animator;
		float _x{ 0.0f };
		float _y{ 0.0f };
		float _width{ 0.0f };
		float _height{ 0.0f };
		bool _initialised{ false };
		bool _reloadOnSizeChanged{ false };
		float _totalAlpha{ 1.0f };
		float _selfAlpha{ 1.0f };
		bool _removeFlag{ false };
		bool _displayed{ true };
		int _level{ 0 };
		// Transition _displayTransition;
		float _displayDelay{ 0.0f };
		float _hideDelay{ 0.0f };


	};

}