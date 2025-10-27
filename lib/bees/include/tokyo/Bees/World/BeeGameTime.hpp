#pragma once

namespace bee
{

	class BeeGameTime
	{
	public:
		BeeGameTime(float daySecondLength);

		void update(float delta);

		float getNormalisedTime() const;

		bool isDay() const;
		bool isNight() const;

	private:
		const float _daySecondLength;
		const float _nightThreshold;
		float _timeOfDay;
	};

}