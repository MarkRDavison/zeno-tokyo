#include <tokyo/Driller/Services/GameCommandService.hpp>

#include <iostream>

namespace drl
{
	GameCommandService::GameCommandService(
		ITerrainAlterationService& _terrainAlterationService,
		IWorkerCreationService& _workerCreationService,
		IShuttleCreationService& _shuttleCreationService,
		IBuildingPlacementService& _buildingPlacementService,
		IJobCreationService& _jobCreationService,
		tokyo::IResourceService& _resourceService
	) : GameCommandService(
		_terrainAlterationService,
		_workerCreationService,
		_shuttleCreationService,
		_buildingPlacementService,
		_jobCreationService,
		_resourceService,
		0ll
	)
	{

	}
	GameCommandService::GameCommandService(
		ITerrainAlterationService& _terrainAlterationService,
		IWorkerCreationService& _workerCreationService,
		IShuttleCreationService& _shuttleCreationService,
		IBuildingPlacementService& _buildingPlacementService,
		IJobCreationService& _jobCreationService,
		tokyo::IResourceService& _resourceService,
		long long _tick
	) : 
		m_CurrentTick(_tick),
		m_IsRecordingCommands(false),
		m_TerrainAlterationService(_terrainAlterationService),
		m_WorkerCreationService(_workerCreationService),
		m_ShuttleCreationService(_shuttleCreationService),
		m_BuildingPlacementService(_buildingPlacementService),
		m_JobCreationService(_jobCreationService),
		m_ResourceService(_resourceService)
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
			return handleDigShaft(_command.commandContext, _command.commandSource, _command.digShaft);
		case GameCommand::EventType::DiggingTile:
			return handleDigTile(_command.commandContext, _command.commandSource, _command.digTile);
		case GameCommand::EventType::PlacingBuilding:
			return handlePlaceBuilding(_command.commandContext, _command.commandSource, _command.placeBuilding);
		case GameCommand::EventType::CreatingWorker:
			return handleCreateWorker(_command.commandContext, _command.commandSource, _command.createWorker);
		case GameCommand::EventType::CreateShuttle:
			return handleCreateShuttle(_command.commandContext, _command.commandSource, _command.createShuttle);
		case GameCommand::EventType::AddResource:
			return handleAddResource(_command.commandContext, _command.commandSource, _command.addResource);
		case GameCommand::EventType::CreateJob:
			return handleCreateJob(_command.commandContext, _command.commandSource, _command.createJob);
		default:
			std::cerr << "Unhandled command type " << (int)_command.type << std::endl;
			return false;
		}
	}

	bool GameCommandService::handleDigShaft(GameCommand::CommandContext _context, GameCommand::CommandSource _source, GameCommand::DigShaftEvent _event)
	{
		// TODO: Consolidate into terrainalterationservice?
		// Should that service know about the command source????
		if (_source == GameCommand::CommandSource::Player)
		{
			auto cost = tokyo::Resource("Resource_Money", 100 * _event.level);

			if (!m_ResourceService.canAfford({cost}) ||
				!m_TerrainAlterationService.isLevelNextShaftLevel(_event.level))
			{
				// TODO: Trigger noise/feedback about not enough money
				return false;
			}

			m_ResourceService.payResource(cost.id, cost.amount);
		}

		return m_TerrainAlterationService.digShaft(_event.level);
	}
	bool GameCommandService::handleDigTile(GameCommand::CommandContext _context, GameCommand::CommandSource _source, GameCommand::DigTileEvent _event)
	{
		return m_TerrainAlterationService.digTile(_event.level, _event.column);
	}
	bool GameCommandService::handlePlaceBuilding(GameCommand::CommandContext _context, GameCommand::CommandSource _source, GameCommand::PlaceBuildingEvent _event)
	{
		return m_BuildingPlacementService.placePrototype(_event.prototypeId, _event.level, _event.column);
	}
	bool GameCommandService::handleCreateWorker(GameCommand::CommandContext _context, GameCommand::CommandSource _source, GameCommand::CreateWorkerEvent _event)
	{
		return m_WorkerCreationService.createWorker(_event.prototypeId, _event.coordinates);
	}
	bool GameCommandService::handleCreateShuttle(GameCommand::CommandContext _context, GameCommand::CommandSource _source, GameCommand::CreateShuttleEvent _event)
	{
		return m_ShuttleCreationService.createShuttle(_event.prototypeId);
	}
	bool GameCommandService::handleAddResource(GameCommand::CommandContext _context, GameCommand::CommandSource _source, GameCommand::AddResourceEvent _event)
	{
		m_ResourceService.updateResource(_event.resource.id, _event.resource.amount);
		return true;
	}
	bool GameCommandService::handleCreateJob(GameCommand::CommandContext _context, GameCommand::CommandSource _source, GameCommand::CreateJobEvent _event)
	{
		return m_JobCreationService.createJob(_event.prototypeId, _event.additionalPrototypeId, _event.coordinates);
	}
}