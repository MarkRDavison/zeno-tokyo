#pragma once

#include <tokyo/Game/Ui/UiConstraint.hpp>

namespace tokyo
{

	class PixelConstraint : public UiConstraint
	{
	public:
		PixelConstraint(int value);
		PixelConstraint(int value, bool flipAxis);

		void completeSetup(UiConstraints* otherConstraints) override;
		float getRelativeValue() override;
		void setPixelValue(int pixels) override;
		void setRelativeValue(float value) override;

	private:
		int _value{ 0 };
		bool _flipAxis{ false };
	};

}