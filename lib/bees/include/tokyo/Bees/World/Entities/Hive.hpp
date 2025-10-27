#pragma once

#include <tokyo/Bees/World/Entities/Entity.hpp>

namespace bee
{

	class Hive : public Entity
	{
	public:
		void update(float) override;
	};

}