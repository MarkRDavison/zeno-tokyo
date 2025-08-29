#include <tokyo/Game/Entity/Entity.hpp>
#include <tokyo/Core/Utils/String.hpp>

namespace tokyo
{

	void Entity::AddTag(const std::string& tag)
	{
		tags.insert(tokyo::String::fnv1a_32(tag));
	}
	void Entity::ClearTag(const std::string& tag)
	{
		tags.erase(tokyo::String::fnv1a_32(tag));
	}
	bool Entity::HasTag(const std::string& tag) const
	{
		return tags.contains(tokyo::String::fnv1a_32(tag));
	}

	void Entity::Update()
	{
		for (auto it = components.begin(); it != components.end();)
		{
			if ((*it)->IsRemoved())
			{
				it = components.erase(it);
				continue;
			}

			if ((*it)->GetEntity() != this)
			{
				(*it)->SetEntity(this);
			}

			if ((*it)->IsEnabled())
			{
				if (!(*it)->started)
				{
					(*it)->Start();
					(*it)->started = true;
				}

				(*it)->Update();
			}

			++it;
		}
	}

	Component* Entity::AddComponent(std::unique_ptr<Component>&& component)
	{
		if (!component) return nullptr;

		component->SetEntity(this);
		return components.emplace_back(std::move(component)).get();
	}

	void Entity::RemoveComponent(Component* component)
	{
		components.erase(std::remove_if(components.begin(), components.end(), [component](const auto& c)
			{
				return c.get() == component;
			}), components.end());
	}

}