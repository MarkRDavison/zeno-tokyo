#pragma once

namespace tokyo
{

	class Entity;
	class Component
	{
		friend class Entity;
	public:
		virtual ~Component() = default;

		virtual void Start() {}
		virtual void Update() {}

		bool IsEnabled() const { return enabled; }
		void SetEnabled(bool _enable) { enabled = _enable; }

		bool IsRemoved() const { return removed; }
		void SetRemoved(bool _removed) { removed = _removed; }

		Entity* GetEntity() const { return entity; }

		void SetEntity(Entity* _entity) { entity = _entity; }

	private:
		bool started = false;
		bool enabled = true;
		bool removed = false;
		Entity* entity = nullptr;
	};

}