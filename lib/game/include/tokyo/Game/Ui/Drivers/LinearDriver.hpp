#pragma once

#include <tokyo/Game/Ui/Drivers/ValueDriver.hpp>

namespace tokyo
{

	class LinearDriver : public ValueDriver
	{
	public:
		LinearDriver(float startValue, float endValue, float length);

		float calculateValue(float time) override;

	private:
		float _startValue;
		float _difference;
	};

}