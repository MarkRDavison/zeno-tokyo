#include <tokyo/Game/Ui/UiConstraints.hpp>
#include <tokyo/Game/Ui/UiConstraint.hpp>
#include <tokyo/Game/Ui/UiComponent.hpp>

namespace tokyo
{

	UiConstraints::UiConstraints(
		UiConstraint* xConstraint,
		UiConstraint* yConstraint,
		UiConstraint* widthConstraint,
		UiConstraint* heightConstraint
	) :
		_xConstraint(xConstraint),
		_yConstraint(yConstraint),
		_widthConstraint(widthConstraint),
		_heightConstraint(heightConstraint)
	{

	}

	void UiConstraints::notifyAdded(UiComponent* current, UiComponent* parent)
	{
		_xConstraint->notifyAdded(this, current, parent);
		_yConstraint->notifyAdded(this, current, parent);
		_widthConstraint->notifyAdded(this, current, parent);
		_heightConstraint->notifyAdded(this, current, parent);
	}

	UiConstraint* UiConstraints::getX() const
	{
		return _xConstraint;
	}
	UiConstraint* UiConstraints::getY() const
	{
		return _yConstraint;
	}
	UiConstraint* UiConstraints::getWidth() const
	{
		return _widthConstraint;
	}
	UiConstraint* UiConstraints::getHeight() const
	{
		return _heightConstraint;
	}

	void UiConstraints::setX(UiConstraint* xConstraint)
	{
		_xConstraint = xConstraint;
		_xConstraint->setAxis(true, true);
	}
	void UiConstraints::setY(UiConstraint* yConstraint)
	{
		_yConstraint = yConstraint;
		_yConstraint->setAxis(false, true);
	}
	void UiConstraints::setWidth(UiConstraint* widthConstraint)
	{
		_widthConstraint = widthConstraint;
		_widthConstraint->setAxis(true, false);
	}
	void UiConstraints::setHeight(UiConstraint* heightConstraint)
	{
		_heightConstraint = heightConstraint;
		_heightConstraint->setAxis(false, false);
	}

}