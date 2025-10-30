#include <tokyo/Game/Ui/Constraints/CenterConstraint.hpp>
#include <tokyo/Game/Ui/UiConstraints.hpp>
#include <stdexcept>

namespace tokyo
{
	void CenterConstraint::completeSetup(UiConstraints* otherConstraints)
	{
		_sizeConstraint = isXAxis()
			? otherConstraints->getWidth()
			: otherConstraints->getHeight();
	}
	float CenterConstraint::getRelativeValue()
	{
		auto relativeSize = _sizeConstraint->getRelativeValue();
		return (1.0f - relativeSize) / 2.0f;
	}
	void CenterConstraint::setPixelValue(int)
	{
		throw std::runtime_error("Cant set a pixel position value for a centered Ui component.");
	}
	void CenterConstraint::setRelativeValue(float)
	{
		throw std::runtime_error("Cant set a relative position value for a centered Ui component.");
	}
}