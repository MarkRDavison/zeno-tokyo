#pragma once

#include <tokyo/Bees/World/Entities/Entity.hpp>
#include <tokyo/Core/Orientation.hpp>

namespace bee
{
	class Player : public Entity
	{
	public:
		void update(float delta) override;

		tokyo::Orientation _orientation{ tokyo::Orientation::RIGHT };
	};
}