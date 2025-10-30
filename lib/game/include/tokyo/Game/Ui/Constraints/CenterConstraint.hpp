#pragma once

#include <tokyo/Game/Ui/UiConstraint.hpp>

namespace tokyo
{

	class CenterConstraint : public UiConstraint
	{
	public:
		void completeSetup(UiConstraints* otherConstraints) override;
		float getRelativeValue() override;
		void setPixelValue(int pixels) override;
		void setRelativeValue(float value) override;

	private:
		UiConstraint* _sizeConstraint{ nullptr };
	};

}