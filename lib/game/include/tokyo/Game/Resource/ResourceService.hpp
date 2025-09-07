#pragma once

#include <tokyo/Game/Resource/Resource.hpp>
#include <tokyo/Core/Utils/Signal.hpp>
#include <unordered_map>

namespace tokyo
{
	class IResourceService
	{
	public:
		virtual ~IResourceService(void) = 0;

		virtual void updateResource(const std::string& _resourceName, ResourceValue _amount) = 0;
		virtual void updateResource(ResourceId _resourceId, ResourceValue _amount) = 0;

		virtual void updateResourceMax(const std::string& _resourceName, ResourceValue _amount) = 0;
		virtual void updateResourceMax(ResourceId _resourceId, ResourceValue _amount) = 0;

		virtual void setResource(const std::string& _resourceName, ResourceValue _amount) = 0;
		virtual void setResource(ResourceId _resourceId, ResourceValue _amount) = 0;

		virtual void setResourceMaximum(const std::string& _resourceName, ResourceValue _maximum) = 0;
		virtual void setResourceMaximum(ResourceId _resourceId, ResourceValue _maximum) = 0;

		virtual ResourceValue getResource(const std::string& _resourceName) = 0;
		virtual ResourceValue getResource(ResourceId _resourceId) = 0;

		virtual ResourceValue getResourceMax(const std::string& _resourceName) = 0;
		virtual ResourceValue getResourceMax(ResourceId _resourceId) = 0;

		virtual bool canAfford(const ResourceBundle& _resourceBundle) = 0;
		virtual bool canAfford(const std::string& _resourceName, ResourceValue _amount) = 0;
		virtual bool canAfford(ResourceId _resourceId, ResourceValue _amount) = 0;
		virtual void payResourceBundle(const ResourceBundle& _resourceBundle) = 0;

		virtual void payResource(const std::string& _resourceName, ResourceValue _amount) = 0;
		virtual void payResource(ResourceId _resourceId, ResourceValue _amount) = 0;

		virtual void receiveResourceBundle(const ResourceBundle& _resourceBundle) = 0;
		virtual void receiveResourceMaxBundle(const ResourceBundle& _resourceBundle) = 0;

		tokyo::Signal<ResourceId> resourceChanged;
	};

	inline IResourceService::~IResourceService(void) = default;

	class ResourceService : public IResourceService
	{
	public:
		~ResourceService(void) override = default;

		void updateResource(const std::string& _resourceName, ResourceValue _amount) override;
		void updateResource(ResourceId _resourceId, ResourceValue _amount) override;

		void updateResourceMax(const std::string& _resourceName, ResourceValue _amount) override;
		void updateResourceMax(ResourceId _resourceId, ResourceValue _amount) override;

		void setResource(const std::string& _resourceName, ResourceValue _amount) override;
		void setResource(ResourceId _resourceId, ResourceValue _amount) override;

		void setResourceMaximum(const std::string& _resourceName, ResourceValue _maximum) override;
		void setResourceMaximum(ResourceId _resourceId, ResourceValue _maximum) override;

		ResourceValue getResource(const std::string& _resourceName) override;
		ResourceValue getResource(ResourceId _resourceId) override;

		ResourceValue getResourceMax(const std::string& _resourceName) override;
		ResourceValue getResourceMax(ResourceId _resourceId) override;

		bool canAfford(const ResourceBundle& _resourceBundle) override;
		bool canAfford(const std::string& _resourceName, ResourceValue _amount) override;
		bool canAfford(ResourceId _resourceId, ResourceValue _amount) override;
		void payResourceBundle(const ResourceBundle& _resourceBundle) override;

		void payResource(const std::string& _resourceName, ResourceValue _amount) override;
		void payResource(ResourceId _resourceId, ResourceValue _amount) override;

		void receiveResourceBundle(const ResourceBundle& _resourceBundle) override;
		void receiveResourceMaxBundle(const ResourceBundle& _resourceBundle) override;

	protected:
		bool resourceExists(ResourceId _resourceId) const;
		LevelResource& getOrCreateResource(ResourceId _resourceId);
		static void revalidateResourceAgainstMaximum(LevelResource& _resource);

	private:
		std::unordered_map<ResourceId, LevelResource> m_ResourceMap;
	};
}