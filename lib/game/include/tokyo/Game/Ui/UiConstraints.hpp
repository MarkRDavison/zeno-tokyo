#pragma once

namespace tokyo
{
	class UiConstraint;
	class UiComponent;
	class UiConstraints
	{
	public:
		UiConstraints(
			UiConstraint* xConstraint,
			UiConstraint* yConstraint,
			UiConstraint* widthConstraint,
			UiConstraint* heightConstraint);

		void notifyAdded(UiComponent* current, UiComponent* parent);

		UiConstraint* getX() const;
		UiConstraint* getY() const;
		UiConstraint* getWidth() const;
		UiConstraint* getHeight() const;

		void setX(UiConstraint* xConstraint);
		void setY(UiConstraint* yConstraint);
		void setWidth(UiConstraint* widthConstraint);
		void setHeight(UiConstraint* heightConstraint);

	protected:
		UiConstraint* _xConstraint{ nullptr };
		UiConstraint* _yConstraint{ nullptr };
		UiConstraint* _widthConstraint{ nullptr };
		UiConstraint* _heightConstraint{ nullptr };
	};

}