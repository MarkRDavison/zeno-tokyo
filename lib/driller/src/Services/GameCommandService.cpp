#include <tokyo/Driller/Services/GameCommandService.hpp>

#include <iostream>

namespace drl
{
	GameCommandService::GameCommandService(
		ITerrainAlterationService& _terrainAlterationService,
		IWorkerCreationService& _workerCreationService,
		IShuttleCreationService& _shuttleCreationService
	) : GameCommandService(
		_terrainAlterationService,
		_workerCreationService,
		_shuttleCreationService,
		0ll
	)
	{

	}
	GameCommandService::GameCommandService(
		ITerrainAlterationService& _terrainAlterationService,
		IWorkerCreationService& _workerCreationService,
		IShuttleCreationService& _shuttleCreationService,
		long long _tick
	) : 
		m_CurrentTick(_tick),
		m_IsRecordingCommands(false),
		m_TerrainAlterationService(_terrainAlterationService),
		m_WorkerCreationService(_workerCreationService),
		m_ShuttleCreationService(_shuttleCreationService)
	{

	}

	void GameCommandService::recordCommands()
	{
		m_IsRecordingCommands = true;
	}
	bool GameCommandService::isRecordingCommands() const
	{
		return m_IsRecordingCommands;
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
		if (m_IsRecordingCommands)
		{
			std::cout << "TODO: Record this command!!!!!! - " << (int)_command.type << std::endl;
		}

		switch (_command.type)
		{
		case GameCommand::EventType::DiggingShaft:
			return handleDigShaft(_command.commandContext, _command.digShaft);
		case GameCommand::EventType::DiggingTile:
			return handleDigTile(_command.commandContext, _command.digTile);
		case GameCommand::EventType::CreatingWorker:
			return handleCreateWorker(_command.commandContext, _command.createWorker);
		case GameCommand::EventType::CreateShuttle:
			return handleCreateShuttle(_command.commandContext, _command.createShuttle);
		default:
			std::cerr << "Unhandled command type " << (int)_command.type << std::endl;
			return false;
		}
	}

	bool GameCommandService::handleDigShaft(GameCommand::CommandContext _context, GameCommand::DigShaftEvent _event)
	{
		return m_TerrainAlterationService.digShaft(_event.level);
	}
	bool GameCommandService::handleDigTile(GameCommand::CommandContext _context, GameCommand::DigTileEvent _event)
	{
		return m_TerrainAlterationService.digTile(_event.level, _event.column);
	}
	bool GameCommandService::handleCreateWorker(GameCommand::CommandContext _context, GameCommand::CreateWorkerEvent _event)
	{
		return m_WorkerCreationService.createWorker(_event.prototypeId, _event.coordinates);
	}
	bool GameCommandService::handleCreateShuttle(GameCommand::CommandContext _context, GameCommand::CreateShuttleEvent _event)
	{
		return m_ShuttleCreationService.createShuttle(_event.prototypeId);
	}
}