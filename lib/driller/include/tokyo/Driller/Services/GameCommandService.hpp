#pragma once

#include <tokyo/Driller/Core/GameCommand.hpp>
#include <tokyo/Driller/Services/TerrainAlterationService.hpp>
#include <tokyo/Driller/Services/Worker/WorkerCreationService.hpp>
#include <tokyo/Driller/Services/Shuttle/ShuttleCreationService.hpp>
#include <tokyo/Driller/Services/Building/BuildingPlacementService.hpp>

namespace drl
{
	class IGameCommandService
	{
	public:
		virtual ~IGameCommandService(void) = 0;

		virtual void tick(void) = 0;
		virtual long long getCurrentTick(void) const = 0;

		virtual bool executeGameCommand(const GameCommand& _command) = 0;
	};

	inline IGameCommandService::~IGameCommandService(void) = default;

	class GameCommandService : public IGameCommandService
	{
	public:
		GameCommandService(
			ITerrainAlterationService& _terrainAlterationService,
			IWorkerCreationService& _workerCreationService,
			IShuttleCreationService& _shuttleCreationService,
			IBuildingPlacementService& _buildingPlacementService
		);
		GameCommandService(
			ITerrainAlterationService& _terrainAlterationService,
			IWorkerCreationService& _workerCreationService,
			IShuttleCreationService& _shuttleCreationService,
			IBuildingPlacementService& _buildingPlacementService,
			long long _tick
		);
		~GameCommandService(void) override = default;

		void recordCommands();
		bool isRecordingCommands() const;

		void tick(void) override;

		long long getCurrentTick(void) const override;

		bool executeGameCommand(const GameCommand& _command) override;

		bool handleDigShaft(GameCommand::CommandContext _context, GameCommand::DigShaftEvent _event);
		bool handleDigTile(GameCommand::CommandContext _context, GameCommand::DigTileEvent _event);
		bool handlePlaceBuilding(GameCommand::CommandContext _context, GameCommand::PlaceBuildingEvent _event);
		bool handleCreateWorker(GameCommand::CommandContext _context, GameCommand::CreateWorkerEvent _event);
		bool handleCreateShuttle(GameCommand::CommandContext _context, GameCommand::CreateShuttleEvent _event);
	private:
		long long m_CurrentTick;
		bool m_IsRecordingCommands;

		ITerrainAlterationService& m_TerrainAlterationService;
		IWorkerCreationService& m_WorkerCreationService;
		IShuttleCreationService& m_ShuttleCreationService;
		IBuildingPlacementService& m_BuildingPlacementService;
	};
}