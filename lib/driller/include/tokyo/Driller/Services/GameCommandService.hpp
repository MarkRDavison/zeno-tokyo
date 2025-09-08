#pragma once

#include <tokyo/Driller/Core/GameCommand.hpp>

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
		GameCommandService();
		GameCommandService(long long _tick);
		~GameCommandService(void) override = default;

		void recordCommands();
		bool isRecordingCommands() const;

		void tick(void) override;

		long long getCurrentTick(void) const override;

		bool executeGameCommand(const GameCommand& _command) override;

		bool handleDigShaft(GameCommand::CommandContext _context, GameCommand::DigShaftEvent _event);

	private:
		long long m_CurrentTick;
		bool m_IsRecordingCommands;
	};
}