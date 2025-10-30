#pragma once

#include <tokyo/Game/Ui/UiComponent.hpp>

namespace tokyo
{
	class UiConstraints;
	class UiConstraint
	{
	public:
		void setAxis(bool xAxis, bool positionValue);
		bool isXAxis() const;
		bool isPositionValue() const;
		UiComponent* getParent()const;
		float getParentPixelSize() const;
		void notifyDimensionChange(bool scaleChange);
		void notifyAdded(UiConstraints *otherConstraints, UiComponent* current, UiComponent* parent);

		virtual void completeSetup(UiConstraints* otherConstraints) = 0;
		virtual float getRelativeValue() = 0;
		virtual void setPixelValue(int pixels) = 0;
		virtual void setRelativeValue(float value) = 0;

	private:
		bool _xAxis{ false };
		bool _positionValue{ false };
		UiComponent* _current{ nullptr };
		UiComponent* _parent{ nullptr };
	};

}