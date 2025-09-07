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

		enum class EventType
		{
			DigShaft,

			Count
		} type;

		union
		{
			DigShaftEvent digShaft;
		};

		explicit GameCommand(const DigShaftEvent& _digShaft) :
			commandContext(CommandContext::DigShaft),
			type(EventType::DigShaft),
			digShaft(_digShaft)
		{

		}
	};

}