#pragma once

#include <string>

namespace bee
{
	struct InventorySlot
	{
		std::string texture;
		std::string name;
		int count{ 0 };
	};
}