#pragma once

#include <tokyo/Driller/Entities/Data/GameData.hpp>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Game/InputActionManager.hpp>

namespace drl
{

	class Game : public tokyo::NonCopyable
	{
	public:
		Game(
			GameData& _gameData,
			tokyo::IInputManager& _inputManager,
			tokyo::IInputActionManager& _inputActionManager
		);

		void update(float _delta);

	private:
		GameData& _gameData;

		tokyo::IInputManager& _inputManager;
		tokyo::IInputActionManager& _inputActionManager;
	};

}