#include <tokyo/Game/Ui/UiConstraint.hpp>
#include <tokyo/Game/Ui/UiConstraints.hpp>

namespace tokyo
{

	void UiConstraint::setAxis(bool xAxis, bool positionValue)
	{
		_xAxis = xAxis;
		_positionValue = positionValue;
	}
	bool UiConstraint::isXAxis() const
	{
		return _xAxis;
	}
	bool UiConstraint::isPositionValue() const
	{
		return _positionValue;
	}
	UiComponent* UiConstraint::getParent()const
	{
		return _parent;
	}
	float UiConstraint::getParentPixelSize() const
	{
		return _xAxis 
			? _parent->getPixelWidth() 
			: _parent->getPixelHeight();
	}
	void UiConstraint::notifyDimensionChange(bool scaleChange)
	{
		_current->notifyDimensionChange(scaleChange);
	}
	void UiConstraint::notifyAdded(UiConstraints* otherConstraints, UiComponent* current, UiComponent* parent)
	{
		_parent = parent;
		_current = current;
		completeSetup(otherConstraints);
	}
		
}