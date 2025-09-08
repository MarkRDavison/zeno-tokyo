#pragma once

#include <tokyo/Game/Scene.hpp>

namespace drl
{
	class SplashScene : public tokyo::Scene
	{
	public:
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


		float m_Percentage{ 0.0f };
	};
}