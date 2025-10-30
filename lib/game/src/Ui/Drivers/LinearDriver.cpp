#include <tokyo/Game/Ui/Drivers/LinearDriver.hpp>

namespace tokyo
{
	LinearDriver::LinearDriver(
		float startValue,
		float endValue,
		float length
	) :
		ValueDriver(length),
		_startValue(startValue),
		_difference(endValue-startValue)
	{

	}

	float LinearDriver::calculateValue(float time)
	{
		return _startValue + (time * _difference);
	}
}