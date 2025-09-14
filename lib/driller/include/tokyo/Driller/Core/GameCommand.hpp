#pragma once

#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Core/Utils/String.hpp>
#include <SFML/System/Vector2.hpp>

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

		struct CreateWorkerEvent
		{
			CreateWorkerEvent(const std::string& _prototypeName, sf::Vector2f _coordinates) :
				prototypeId((IdType)tokyo::String::fnv1a_32(_prototypeName)),
				coordinates(_coordinates)
			{
			}

			IdType prototypeId{ 0 };
			sf::Vector2f coordinates;
		};

		enum class CommandContext
		{
			DigShaft,
			DigTile,
			CreateWorker,

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
			CreateWorker,

			Count
		} type;

		union
		{
			DigShaftEvent digShaft;
			DigTileEvent digTile;
			CreateWorkerEvent createWorker;
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

		explicit GameCommand(const CreateWorkerEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::CreateWorker),
			createWorker(_event)
		{

		}
	};

}