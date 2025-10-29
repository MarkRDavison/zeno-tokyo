#pragma once

#include <tokyo/Bees/World/Entities/Entity.hpp>
#include <tokyo/Bees/Data/BeeData.hpp>
#include <unordered_map>
#include <vector>

namespace bee
{

	enum class HiveType
	{
		Common,
		Agricultural,
		Metal,
		Gem
	};

	class Hive : public Entity
	{
	public:
		Hive(HiveType type, int maxSlots, int inventoryCapacity);

		void update(float) override;

		bool addBee(const BeeData& bee);

		bool removeBee(const std::string& species);

		int getBeeCount() const;

		const std::unordered_map<std::string, int>& getInventory() const;

	private:
		const HiveType _type;
		const int _maxSlots;
		const int _inventoryCapacity; 
		
		std::vector<BeeData> _bees;

		std::unordered_map<std::string, int> _inventory;
		std::unordered_map<std::string, float> _progressProductivity;
	};

}