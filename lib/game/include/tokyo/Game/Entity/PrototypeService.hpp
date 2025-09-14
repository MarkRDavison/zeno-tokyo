#pragma once

#include <tokyo/Game/Entity/IdentityService.hpp>
#include <tokyo/Core/Utils/String.hpp>

namespace tokyo
{
	template <typename TPrototype, typename TInstance, typename TPrototypeId>
	class IPrototypeService
	{
	public:
		virtual ~IPrototypeService(void) = default;

		virtual TPrototypeId getPrototypeId(const std::string& _prototypeName) const = 0;

		virtual void registerPrototype(const std::string& _prototypeName, const TPrototype& _prototype) = 0;
		virtual void registerPrototype(TPrototypeId _prototypeId, const TPrototype& _prototype) = 0;

		virtual const TPrototype& getPrototype(const std::string& _prototypeName) const = 0;
		virtual const TPrototype& getPrototype(TPrototypeId _prototypeId) const = 0;

		virtual TInstance createInstance(const std::string& _prototypeName) const = 0;
		virtual TInstance createInstanceById(TPrototypeId _prototypeId) const = 0;

		virtual bool isPrototypeRegistered(const std::string& _prototypeName) const = 0;
		virtual bool isPrototypeRegistered(TPrototypeId _prototypeId) const = 0;

		virtual std::vector<TPrototype> getPrototypes() const = 0;
	};

	template <typename TPrototype, typename TInstance, typename TPrototypeId>
	class PrototypeService : public IPrototypeService<TPrototype, TInstance, TPrototypeId>
	{
	public:
		PrototypeService(IIdentificationService<TPrototypeId>& _identificationService) :
			m_IdentificationService(_identificationService)
		{

		}
		~PrototypeService(void) override = default;

		TPrototypeId getPrototypeId(const std::string& _prototypeName) const override
		{
			return (TPrototypeId)String::fnv1a_32(_prototypeName);
		}

		void registerPrototype(const std::string& _prototypeName, const TPrototype& _prototype) override
		{
			const TPrototypeId id = getPrototypeId(_prototypeName);
			if (m_NamePrototypeMap.find(id) == m_NamePrototypeMap.end())
			{
				m_PrototypeIdNameMap[id] = _prototypeName;
			}
			registerPrototype(id, _prototype);
		}
		void registerPrototype(TPrototypeId _prototypeId, const TPrototype& _prototype) override
		{
			if (!isPrototypeRegistered(_prototypeId))
			{
				m_NamePrototypeMap[_prototypeId] = _prototype;
			}
		}

		const TPrototype& getPrototype(const std::string& _prototypeName) const override
		{
			return getPrototype(getPrototypeId(_prototypeName));
		}
		const TPrototype& getPrototype(TPrototypeId _prototypeId) const override
		{
			if (isPrototypeRegistered(_prototypeId))
			{
				return m_NamePrototypeMap.at(_prototypeId);
			}

			throw std::logic_error("Prototype is not registered.");
		}

		TInstance createInstance(const std::string& _prototypeName) const override
		{
			return createInstanceById(getPrototypeId(_prototypeName));
		}
		TInstance createInstanceById(TPrototypeId _prototypeId) const override
		{
			return createInstance(getPrototype(_prototypeId));
		}
		virtual TInstance createInstance(const TPrototype& _prototype) const = 0;

		bool isPrototypeRegistered(const std::string& _prototypeName) const override
		{
			return isPrototypeRegistered(getPrototypeId(_prototypeName));
		}
		bool isPrototypeRegistered(TPrototypeId _prototypeId) const override
		{
			return m_NamePrototypeMap.find(_prototypeId) != m_NamePrototypeMap.end();
		}

		std::vector<TPrototype> getPrototypes() const override
		{
			std::vector<TPrototype> vec;
			for (const auto& [k, v] : m_NamePrototypeMap)
			{
				vec.push_back(v);
			}

			return vec;
		}

	protected:
		IIdentificationService<TPrototypeId>& m_IdentificationService;

		std::unordered_map<TPrototypeId, std::string> m_PrototypeIdNameMap;
		std::unordered_map<TPrototypeId, TPrototype> m_NamePrototypeMap;
	};
}