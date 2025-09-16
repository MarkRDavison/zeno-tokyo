#include <tokyo/Game/Resource/ResourceService.hpp>

#include <stdexcept>

namespace tokyo
{
	void ResourceService::updateResource(const std::string& _resourceName, ResourceValue _amount)
	{
		updateResource((ResourceId)tokyo::String::fnv1a_32(_resourceName), _amount);
	}
	void ResourceService::updateResource(ResourceId _resourceId, ResourceValue _amount)
	{
		setResource(_resourceId, _amount + getResource(_resourceId));
	}

	void ResourceService::updateResourceMax(const std::string& _resourceName, ResourceValue _amount)
	{
		updateResourceMax((ResourceId)tokyo::String::fnv1a_32(_resourceName), _amount);
	}
	void ResourceService::updateResourceMax(ResourceId _resourceId, ResourceValue _amount)
	{
		setResourceMaximum(_resourceId, getResourceMax(_resourceId) + _amount);
	}

	void ResourceService::setResource(const std::string& _resourceName, ResourceValue _amount)
	{
		setResource((ResourceId)tokyo::String::fnv1a_32(_resourceName), _amount);
	}
	void ResourceService::setResource(ResourceId _resourceId, ResourceValue _amount)
	{
		LevelResource& resource = getOrCreateResource(_resourceId);
		resource.resource.amount = _amount;
		revalidateResourceAgainstMaximum(resource);
		resourceChanged.invoke(_resourceId);
	}

	void ResourceService::setResourceMaximum(const std::string& _resourceName, ResourceValue _maximum)
	{
		setResourceMaximum((ResourceId)tokyo::String::fnv1a_32(_resourceName), _maximum);
	}
	void ResourceService::setResourceMaximum(ResourceId _resourceId, ResourceValue _maximum)
	{
		LevelResource& resource = getOrCreateResource(_resourceId);
		resource.max = _maximum;
		revalidateResourceAgainstMaximum(resource);
		resourceChanged.invoke(_resourceId);
	}

	ResourceValue ResourceService::getResource(const std::string& _resourceName)
	{
		return getResource((ResourceId)tokyo::String::fnv1a_32(_resourceName));
	}
	ResourceValue ResourceService::getResource(ResourceId _resourceId)
	{
		return getOrCreateResource(_resourceId).resource.amount;
	}

	LevelResource ResourceService::getExistingResource(const std::string& _resourceName) const
	{
		return getExistingResource((ResourceId)tokyo::String::fnv1a_32(_resourceName));
	}
	LevelResource ResourceService::getExistingResource(ResourceId _resourceId) const
	{
		const auto& iter = m_ResourceMap.find(_resourceId);
		if (iter == m_ResourceMap.end())
		{
			throw std::runtime_error("getExistingResource called on non-existant resource");
		}

		return (*iter).second;
	}

	ResourceValue ResourceService::getResourceMax(const std::string& _resourceName)
	{
		return getResourceMax((ResourceId)tokyo::String::fnv1a_32(_resourceName));
	}
	ResourceValue ResourceService::getResourceMax(ResourceId _resourceId)
	{
		return getOrCreateResource(_resourceId).max;
	}

	bool ResourceService::canAfford(const ResourceBundle& _resourceBundle)
	{
		for (const Resource& _res : _resourceBundle)
		{

			if (_res.amount == 0)
			{
				continue;
			}

			if (!resourceExists(_res.id))
			{
				return false;
			}

			if (getResource(_res.id) < _res.amount)
			{
				return false;
			}

		}

		return true;
	}
	bool ResourceService::canAfford(const std::string& _resourceName, ResourceValue _amount)
	{
		return canAfford((ResourceId)tokyo::String::fnv1a_32(_resourceName), _amount);
	}
	bool ResourceService::canAfford(ResourceId _resourceId, ResourceValue _amount)
	{
		if (m_ResourceMap.find(_resourceId) == m_ResourceMap.end())
		{
			return false;
		}

		if (!resourceExists(_resourceId))
		{
			return false;
		}

		return _amount <= getResource(_resourceId);
	}
	void ResourceService::payResourceBundle(const ResourceBundle& _resourceBundle)
	{
		for (const Resource& _res : _resourceBundle)
		{
			if (_res.amount == 0)
			{
				continue;
			}

			updateResource(_res.id, -_res.amount);
		}
	}

	void ResourceService::payResource(const std::string& _resourceName, ResourceValue _amount)
	{
		payResource((ResourceId)tokyo::String::fnv1a_32(_resourceName), _amount);
	}
	void ResourceService::payResource(ResourceId _resourceId, ResourceValue _amount)
	{
		if (m_ResourceMap.find(_resourceId) == m_ResourceMap.end())
		{
			return;
		}

		if (!resourceExists(_resourceId))
		{
			return;
		}

		updateResource(_resourceId, -_amount);
	}

	void ResourceService::receiveResourceBundle(const ResourceBundle& _resourceBundle)
	{
		for (const Resource& _res : _resourceBundle)
		{
			if (_res.amount == 0)
			{
				continue;
			}

			updateResource(_res.id, _res.amount);
		}
	}
	void ResourceService::receiveResourceMaxBundle(const ResourceBundle& _resourceBundle)
	{
		for (const Resource& _res : _resourceBundle)
		{
			if (_res.amount == 0)
			{
				continue;
			}

			updateResourceMax(_res.id, _res.amount);
		}
	}

	bool ResourceService::resourceExists(ResourceId _resourceId) const
	{
		return m_ResourceMap.find(_resourceId) != m_ResourceMap.end();
	}
	LevelResource& ResourceService::getOrCreateResource(ResourceId _resourceId)
	{
		auto iter = m_ResourceMap.find(_resourceId);
		if (iter == m_ResourceMap.end())
		{
			m_ResourceMap[_resourceId].resource.id = _resourceId;
		}

		return m_ResourceMap[_resourceId];
	}
	void ResourceService::revalidateResourceAgainstMaximum(LevelResource& _resource)
	{
		if (_resource.resource.amount > _resource.max && _resource.max != -1)
		{
			_resource.resource.amount = _resource.max;
		}
	}
}