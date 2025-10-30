#include <tokyo/Game/Ui/Drivers/ValueDriver.hpp>
#include <cassert>

namespace tokyo
{

	ValueDriver::ValueDriver(
		float length
	) : ValueDriver(0.0f, length)
	{

	}
	
	ValueDriver::ValueDriver(
		float startTime,
		float length
	) :
		_startTime(startTime),
		_length(length)
	{

	}

	float ValueDriver::update(float delta)
	{
		_currentTime += delta;

		if (_currentTime < _startTime)
		{
			_currentValue = calculateValue(0.0f);
			return _currentValue;
		}

		auto totalTime = _length + _startTime;

		if (_currentTime >= totalTime)
		{
			_currentTime -= totalTime;
			assert(_currentTime < totalTime);
			_firstPeriodDone = true;
		}

		auto relativeTime = (_currentTime - _startTime) / _length;
		_currentValue = calculateValue(relativeTime);
		return _currentValue;
	}

	bool ValueDriver::hasCompletedOnePeriod() const
	{
		return _firstPeriodDone;
	}
	float ValueDriver::getCurrentValue() const
	{
		return _currentValue;
	}
}