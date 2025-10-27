#pragma once

namespace bee
{
	class Entity
	{
	public:
		virtual ~Entity() = default;

		virtual void update(float) {}

		int TileX{ 0 };
		int TileY{ 0 };
		float X{ 0.0f };
		float Y{ 0.0f };
	};
}