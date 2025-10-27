#include <tokyo/Bees/BeeInstance.hpp>

namespace bee
{
	thread_local BeeInstance* BeeInstance::_instance{ nullptr };

	BeeInstance::BeeInstance(
		tokyo::Application& application
	) : 
		GameTime(60.0f),
		_application(application),
		InputManager(_application.getWindow()),
		InputActionManager(InputManager),
		FileManager()
	{

	}
}