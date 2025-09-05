#pragma once

#include <tokyo/Game/Scene.hpp>

namespace drl
{
	class SplashScene : public tokyo::Scene
	{
	public:
		void Update(float delta) override;

		float m_Percentage{ 0.0f };
	};
}