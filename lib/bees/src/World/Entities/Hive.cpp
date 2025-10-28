#include <tokyo/Bees/World/Entities/Hive.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Bees/Constants.hpp>
#include <iostream>

namespace bee
{
	Hive::Hive(
		HiveType type
	) :
		_type(type)
	{

	}

	void Hive::update(float)
	{
		std::cout << "Hive type: " << (int)_type << std::endl;
	}

}