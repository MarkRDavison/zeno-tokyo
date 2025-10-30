#pragma once

#include <tokyo/Game/Ui/UiConstraint.hpp>

namespace tokyo
{
	class FillConstraint : public UiConstraint
	{
	public:
		FillConstraint(int pixelGap);

		void completeSetup(UiConstraints* otherConstraints) override;
		float getRelativeValue() override;
		void setPixelValue(int pixels) override;
		void setRelativeValue(float value) override;

	private:
		int _pixelGap{ 0 };
		UiConstraint* _positionConstraint{ nullptr };
	};
}