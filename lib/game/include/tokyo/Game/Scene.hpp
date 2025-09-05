#pragma once

#include <tokyo/Game/Entity/EntityHolder.hpp>
#include <tokyo/Game/Entity/SystemHolder.hpp>

namespace tokyo
{
	class Scene
	{
	public:
		void UpdateScene(float delta)
		{
			if (!active)
			{
				return;
			}

			if (!started)
			{
				Start();
				started = true;
			}

			Update(delta);
		}

		bool IsActive() const { return this->active; }
		void SetActive(bool active) { this->active = active; }

		std::vector<Entity*> QueryAll() { return entities.QueryAll(); }

	protected:
		virtual void Update(float delta) = 0;
		virtual void Start() {}

	protected:
		bool started{ false };
		bool active{ true };

		SystemHolder systems;

		EntityHolder entities;
	};

}