#include <tokyo/Driller/Services/GameCommandService.hpp>

#include <iostream>

namespace drl
{
	GameCommandService::GameCommandService() : GameCommandService(0ll)
	{

	}
	GameCommandService::GameCommandService(
		long long _tick
	) : 
		m_CurrentTick(_tick)
	{

	}

	void GameCommandService::tick(void)
	{
		m_CurrentTick++;
	}

	long long GameCommandService::getCurrentTick(void) const
	{
		return m_CurrentTick;
	}

	bool GameCommandService::executeGameCommand(const GameCommand& _command)
	{
		switch (_command.type)
		{
		case GameCommand::EventType::DigShaft:
			return handleDigShaft(_command.commandContext, _command.digShaft);
		default:
			std::cerr << "Unhandled command type " << (int)_command.type << std::endl;
			return false;
		}
	}

	bool GameCommandService::handleDigShaft(GameCommand::CommandContext _context, GameCommand::DigShaftEvent _event)
	{
		throw std::exception("Not Implemented.");
	}
}