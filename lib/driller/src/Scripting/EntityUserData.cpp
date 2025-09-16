#include <tokyo/Driller/Scripting/EntityUserData.hpp>
#include <tokyo/Driller/Entities/Job.hpp>
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

        _state.new_usertype<drl::JobInstance>(
            "JobInstance",
            "Id", sol::readonly(&drl::JobInstance::Id),
            "prototypeId", &drl::JobInstance::prototypeId,
            "additionalPrototypeId", &drl::JobInstance::additionalPrototypeId,
            "allocatedWorkerId", &drl::JobInstance::allocatedWorkerId,
            "tile", &drl::JobInstance::tile,
            "offset", &drl::JobInstance::offset,
            "requiresRemoval", &drl::JobInstance::requiresRemoval,
            "work", &drl::JobInstance::work
        );
	}
}