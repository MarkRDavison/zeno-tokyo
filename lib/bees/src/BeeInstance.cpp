#include <tokyo/Bees/BeeInstance.hpp>

namespace bee
{
	BeeInstance* BeeInstance::_instance{ nullptr };


	BeeInstance::BeeInstance(
		tokyo::Application& application
	) : 
		_application(application),
		InputManager(_application.getWindow()),
		InputActionManager(InputManager),
		FileManager()
	{

	}
}