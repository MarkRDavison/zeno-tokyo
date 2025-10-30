#include <tokyo/Game/Ui/Constraints/FillConstraint.hpp>
#include <tokyo/Game/Ui/UiConstraints.hpp>
#include <cmath>

namespace tokyo
{
	FillConstraint::FillConstraint(
		int pixelGap
	) :
		_pixelGap(pixelGap)
	{

	}

	void FillConstraint::completeSetup(UiConstraints* otherConstraints)
	{
		_positionConstraint = isXAxis()
			? otherConstraints->getX()
			: otherConstraints->getY();
	}
	float FillConstraint::getRelativeValue()
	{
		auto relativePosition = _positionConstraint->getRelativeValue();

		auto parentSizePixels = isXAxis()
			? getParent()->getPixelWidth()
			: getParent()->getPixelHeight();

		auto relativeGap = _pixelGap / parentSizePixels;

		return 1.0f - (relativeGap + relativePosition);

	}
	void FillConstraint::setPixelValue(int pixels)
	{
		if (_pixelGap == pixels)
		{
			return;
		}

		_pixelGap = pixels;
		notifyDimensionChange(true);
	}
	void FillConstraint::setRelativeValue(float value)
	{
		auto parentSizePixels = isXAxis()
			? getParent()->getPixelWidth()
			: getParent()->getPixelHeight();

		_pixelGap = (int)std::roundf(parentSizePixels * value);
		notifyDimensionChange(true);
	}
}