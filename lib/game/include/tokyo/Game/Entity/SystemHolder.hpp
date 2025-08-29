#pragma once

#include <tokyo/Core/Log.hpp>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Core/Utils/TypeInfo.hpp>
#include <tokyo/Game/Entity/System.hpp>
#include <unordered_map>
#include <memory>

namespace tokyo
{

	class SystemHolder : NonCopyable
	{
	public:
		template<typename T,
			typename = std::enable_if_t<std::is_convertible_v<T*, System*>>>
		bool Has() const
		{
			const auto it = systems.find(TypeInfo<System>::GetTypeId<T>());

			return it != systems.end() && it->second;
		}

		template<typename T,
			typename = std::enable_if_t<std::is_convertible_v<T*, System*>>>
		T* Get() const
		{
			auto it = systems.find(TypeInfo<System>::GetTypeId<T>());

			if (it == systems.end() || !it->second)
			{
				return nullptr;
			}

			return static_cast<T*>(it->second.get());
		}

		template<typename T,
			typename = std::enable_if_t<std::is_convertible_v<T*, System*>>>
		void Add(std::unique_ptr<T>&& system)
		{
			Remove<T>();

			const auto typeId = TypeInfo<System>::GetTypeId<T>();

			systems[typeId] = std::move(system);
		}

		template<typename T,
			typename = std::enable_if_t<std::is_convertible_v<T*, System*>>>
		void Remove()
		{
			const auto typeId = TypeInfo<System>::GetTypeId<T>();

			systems.erase(typeId);
		}

		void Clear();

		template<typename Func>
		void ForEach(Func&& func)
		{
			for (auto& [typeId, system] : systems)
			{
				try
				{
					func(typeId, system.get());
				}
				catch (const std::exception& e)
				{
					Log::Error(e.what(), '\n');
				}
			}
		}
	private:
		std::unordered_map<TypeId, std::unique_ptr<System>> systems;
	};

}