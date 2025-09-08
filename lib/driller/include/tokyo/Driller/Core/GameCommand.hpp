#pragma once

namespace drl
{

	struct GameCommand
	{

		struct DigShaftEvent
		{
			DigShaftEvent(int _level) : level(_level) {}
			int level{ 0 };
		};

		enum class CommandContext
		{
			DigShaft,

			Undefined
		} commandContext{ CommandContext::Undefined };

		enum class CommandSource
		{
			Setup,
			Player,
			System
		} commandSource{ CommandSource::Player };

		enum class EventType
		{
			DigShaft,

			Count
		} type;

		union
		{
			DigShaftEvent digShaft;
		};

		explicit GameCommand(const DigShaftEvent& _digShaft, CommandSource _commandSource) :
			commandContext(CommandContext::DigShaft),
			commandSource(_commandSource),
			type(EventType::DigShaft),
			digShaft(_digShaft)
		{

		}
	};

}