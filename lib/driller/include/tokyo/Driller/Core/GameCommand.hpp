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
		} commandContext{ CommandContext::Undefined }; // TODO: Way to inherit context scope?

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

		explicit GameCommand(const DigShaftEvent& _digShaft, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::DigShaft),
			digShaft(_digShaft)
		{

		}
	};

}