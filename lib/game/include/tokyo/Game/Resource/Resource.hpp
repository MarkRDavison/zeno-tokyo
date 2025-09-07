#pragma once

#include <tokyo/Core/Utils/String.hpp>
#include <vector>

namespace tokyo
{

	using ResourceId = long long;
	using ResourceValue = int;

	static_assert(std::is_signed<ResourceId>());
	static_assert(std::is_signed<ResourceValue>());

	struct Resource
	{
		Resource(void) :
			Resource(0, 0)
		{
		}
		Resource(
			ResourceId _id,
			ResourceValue _amount
		) :
			id(_id),
			amount(_amount)
		{
		}
		Resource(
			const std::string& _name,
			ResourceValue _amount
		) :
			id((ResourceId)tokyo::String::fnv1a_32(_name)),
			amount(_amount)
		{
		}

		ResourceId id;
		ResourceValue amount;
	};

	struct LevelResource
	{
		LevelResource(
		) :
			LevelResource(
				{},
				-1
			)
		{
		}
		LevelResource(
			Resource _resource,
			ResourceValue _max
		) :
			resource(_resource),
			max(_max)
		{
		}

		Resource resource;
		ResourceValue max;
	};

	using ResourceBundle = std::vector<Resource>;
}