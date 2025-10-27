#include <tokyo/Bees/World/BeeGameTime.hpp>
#include <tokyo/Core/Log.hpp>

namespace bee
{
	BeeGameTime::BeeGameTime(
		float daySecondLength
	) :
		_daySecondLength(daySecondLength),
		_nightThreshold(0.75),
		_timeOfDay(0.0f)
	{

	}

	void BeeGameTime::update(float delta)
	{
		auto wasDay = isDay();

		_timeOfDay += delta;
		if (_timeOfDay >= _daySecondLength)
		{
			_timeOfDay -= _daySecondLength;
		}

		auto isNowDay = isDay();

		if (wasDay != isNowDay)
		{
			if (isNowDay)
			{
				// TODO: Trigger an event?
				tokyo::Log::Debug("It is a new day\n");
			}
			else
			{
				// TODO: Trigger an event?
				tokyo::Log::Debug("It is now night\n");
			}
		}
	}

	float BeeGameTime::getNormalisedTime() const
	{
		return _timeOfDay / _daySecondLength;
	}

	float BeeGameTime::getNightThreshold() const
	{
		return _nightThreshold;
	}

	bool BeeGameTime::isDay() const
	{
		return getNormalisedTime() < _nightThreshold;
	}
	bool BeeGameTime::isNight() const
	{
		return !isDay();
	}
}