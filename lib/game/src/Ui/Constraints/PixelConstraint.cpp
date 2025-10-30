#include <tokyo/Game/Ui/Constraints/PixelConstraint.hpp>
#include <cmath>

namespace tokyo
{
	PixelConstraint::PixelConstraint(
		int value
	) : PixelConstraint(value, false)
	{

	}

	PixelConstraint::PixelConstraint(
		int value,
		bool flipAxis
	) :
		_value(value),
		_flipAxis(flipAxis)
	{

	}

	void PixelConstraint::completeSetup(UiConstraints*)
	{

	}
	float PixelConstraint::getRelativeValue()
	{
		auto parentSizePixels = isXAxis()
			? getParent()->getPixelWidth()
			: getParent()->getPixelHeight();

		auto relValue = _value / parentSizePixels;

		return _flipAxis
			? 1.0f - relValue
			: relValue;
	}
	void PixelConstraint::setPixelValue(int pixels)
	{
		if (_value == pixels)
		{
			return;
		}

		_value = pixels;
		notifyDimensionChange(!isPositionValue());
	}
	void PixelConstraint::setRelativeValue(float value)
	{
		auto newValue = _flipAxis
			? 1.0f - value
			: value;

		_value = (int)std::roundf(getParentPixelSize() * newValue);
		notifyDimensionChange(!isPositionValue());
	}

}