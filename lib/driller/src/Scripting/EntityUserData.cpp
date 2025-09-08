#include <tokyo/Driller/Scripting/EntityUserData.hpp>
#include <tokyo/Game/Resource/Resource.hpp>
#include <sol/sol.hpp>

namespace drl
{
	void EntityUserData::generateEntitiesUserData(sol::state& _state)
	{

        _state.new_usertype<tokyo::Resource>(
            "Resource",
            sol::constructors<
            tokyo::Resource(),
            tokyo::Resource(tokyo::ResourceId, tokyo::ResourceValue),
            tokyo::Resource(std::string, tokyo::ResourceValue)
            >(),
            "id", &tokyo::Resource::id,
            "amount", &tokyo::Resource::amount
        );

        _state.new_usertype<tokyo::LevelResource>(
            "LevelResource",
            sol::constructors<
            tokyo::LevelResource(),
            tokyo::LevelResource(tokyo::Resource, tokyo::ResourceValue)
            >(),
            "resource", &tokyo::LevelResource::resource,
            "max", &tokyo::LevelResource::max
        );
	}
}