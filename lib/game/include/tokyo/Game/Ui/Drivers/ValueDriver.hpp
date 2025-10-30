#pragma once

namespace tokyo
{
	class ValueDriver
	{
	public:
		ValueDriver(float length);
		ValueDriver(float startTime, float length);

		float update(float delta);
		virtual float calculateValue(float time) = 0;

		bool hasCompletedOnePeriod() const;
		float getCurrentValue() const;

	private:
		float _startTime{ 0.0f };
		float _length{ 0.0f };
		float _currentTime{ 0.0f };
		float _currentValue{ 0.0f };
		bool _firstPeriodDone{ false };
	};
}