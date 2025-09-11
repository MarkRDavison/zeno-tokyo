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

		struct DigTileEvent
		{
			DigTileEvent(int _level, int _column) : level(_level), column(_column) {}
			int level{ 0 };
			int column{ 0 };
		};

		enum class CommandContext
		{
			DigShaft,
			DigTile,

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
			DigTile,

			Count
		} type;

		union
		{
			DigShaftEvent digShaft;
			DigTileEvent digTile;
		};

		explicit GameCommand(const DigShaftEvent& _digShaft, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::DigShaft),
			digShaft(_digShaft)
		{

		}

		explicit GameCommand(const DigTileEvent& _digTile, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::DigTile),
			digTile(_digTile)
		{

		}
	};

}