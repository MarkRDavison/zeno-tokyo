#pragma once

namespace tokyo
{

	class UiComponent
	{
	public:
		float getPixelWidth() const;
		float getPixelHeight() const;
		void notifyDimensionChange(bool scaleChange);
	};

}