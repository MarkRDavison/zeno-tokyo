#include <tokyo/Bees/World/Entities/Hive.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Bees/Constants.hpp>
#include <iostream>
#include <cmath>

namespace bee
{
	Hive::Hive(
		HiveType type, 
		int maxSlots, 
		int inventoryCapacity
	) :
		_type(type),
		_maxSlots(maxSlots),
		_inventoryCapacity(inventoryCapacity)
	{
		std::cout << "Hive type: " << (int)_type << ", max slots: " << _maxSlots << ", capacity: " << _inventoryCapacity << std::endl;
	}

	void Hive::update(float delta)
	{
		if (getBeeCount() <= 0)
		{
			return;
		}

		for (const auto& b : _bees)
		{
			_progressProductivity[b.species] += b.productivity * delta;
		}

		for (auto& [k, v] : _progressProductivity)
		{
			if (v > 1.0f)
			{
				_inventory[k] = std::min(_inventory[k] + 1, _inventoryCapacity);
				v -= 1.0f;
			}
		}
	}

	bool Hive::addBee(const BeeData& bee)
	{
		if (getBeeCount() >= _maxSlots)
		{
			return false;
		}

		_bees.push_back(bee);

		return true;
	}

	bool Hive::removeBee(const std::string& species)
	{
		for (size_t i = 0; i < _bees.size(); ++i)
		{
			if (_bees[i].species == species)
			{
				_bees.erase(_bees.begin() + i);
				return true;
			}
		}

		return false;
	}

	int Hive::getBeeCount() const
	{
		return (int)_bees.size();
	}

	const std::unordered_map<std::string, int>& Hive::getInventory() const
	{
		return _inventory;
	}
}