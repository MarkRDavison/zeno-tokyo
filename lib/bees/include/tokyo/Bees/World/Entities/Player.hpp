#pragma once

#include <tokyo/Bees/World/Entities/Entity.hpp>
#include <tokyo/Core/Orientation.hpp>
#include <tokyo/Bees/Constants.hpp>
#include <tokyo/Bees/Data/InventorySlot.hpp>
#include <array>

namespace bee
{
	class Player : public Entity
	{
	public:
		void update(float delta) override;

		tokyo::Orientation _orientation{ tokyo::Orientation::RIGHT };

		int getActiveInventorySlot() const;
		void setActiveInventorySlot(int slotIndex);

		InventorySlot& getInventoryAtSlot(int slotIndex);
		const InventorySlot& getInventoryAtSlot(int slotIndex) const;

	private:
		sf::Vector2i getFacedTile() const;
		int _slotIndex{ 0 };
		std::array<InventorySlot, Constants::InventorySlots> _inventory;
	};
}