#pragma once

#include <tokyo/Bees/World/Entities/Entity.hpp>

namespace bee
{

	enum class HiveType
	{
		Common
	};

	class Hive : public Entity
	{
	public:
		Hive(HiveType type);
		void update(float) override;

	private:
		const HiveType _type;
	};

}