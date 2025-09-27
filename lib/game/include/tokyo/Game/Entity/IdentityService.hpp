#pragma once

#include <string>
#include <unordered_map>
#include <tokyo/Core/Utils/String.hpp>

namespace tokyo
{
	template <typename T>
	class IIdentificationService
	{
	public:
		virtual ~IIdentificationService(void) = 0;

		virtual T generateId(void) = 0;

		virtual void registerName(const std::string& _name) = 0;
		virtual std::string retrieveName(T _id) const = 0;
	};

	template <typename T>
	inline IIdentificationService<T>::~IIdentificationService() = default;

	template <typename T>
	class IdentificationService : public IIdentificationService<T>
	{
	public:
		~IdentificationService(void) override = default;

		T generateId(void) override
		{
			return m_EntityId++;
		}

		void registerName(const std::string& _name) override
		{
			m_NameLookups[(T)String::fnv1a_32(_name)] = _name;
		}
		std::string retrieveName(T _id) const override
		{
			const auto& res = m_NameLookups.find(_id);
			return res == m_NameLookups.end() ? "<<unknown id>>" : (*res).second;
		}

	private:
		T m_EntityId{ 1 };
		std::unordered_map<T, std::string> m_NameLookups;
	};
}