#pragma once

#include <tokyo/Game/Scene.hpp>
#include <tokyo/Bees/Graphics/Inventory.hpp>

namespace bee
{
	class GameScene : public tokyo::Scene
	{
	public:
		void start() override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		Inventory _inventory;
	};
}