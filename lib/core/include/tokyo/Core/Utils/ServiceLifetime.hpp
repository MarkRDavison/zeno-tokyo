#pragma once

namespace tokyo
{
	enum class ServiceLifetime : int 
	{ 
		Transient = 0, 
		Scoped = 1, 
		Singleton = 2
	};
}