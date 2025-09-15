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

		struct PlaceBuildingEvent
		{
			PlaceBuildingEvent(void) {}
			PlaceBuildingEvent(const std::string& _prototypeName, int _level, int _column) :
				prototypeId((IdType)tokyo::String::fnv1a_32(_prototypeName)),
				level(_level),
				column(_column)
			{
			}
			PlaceBuildingEvent(IdType _prototypeId, int _level, int _column) :
				prototypeId(_prototypeId),
				level(_level),
				column(_column)
			{
			}
			IdType prototypeId{ 0 };
			int level{ 0 };
			int column{ 0 };
		};

		struct CreateShuttleEvent
		{
			CreateShuttleEvent(void) {}
			CreateShuttleEvent(const std::string& _prototypeName) :
				prototypeId((IdType)tokyo::String::fnv1a_32(_prototypeName))
			{
			}

			IdType prototypeId{ 0 };
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

		struct CreateJobEvent
		{
			CreateJobEvent(void) {}
			CreateJobEvent(const std::string& _prototypeName, const std::string& _additionalPrototypeName, sf::Vector2i _coordinates) :
				prototypeId((IdType)tokyo::String::fnv1a_32(_prototypeName)),
				additionalPrototypeId((IdType)tokyo::String::fnv1a_32(_additionalPrototypeName)),
				coordinates(_coordinates)
			{
			}
			IdType prototypeId{ 0 };
			IdType additionalPrototypeId{ 0 };
			sf::Vector2i coordinates;
		};

		enum class CommandContext
		{
			DigShaft,
			DigTile,
			CreateWorker,
			CreatingShuttle,
			CreatingWorker,
			CreatingJob,
			PlaceBuilding,

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
			CreateShuttle,
			CreateWorker,
			CreateJob,
			PlaceBuilding,

			Count
		} type;

		union
		{
			DigTileEvent digTile;
			DigShaftEvent digShaft;
			CreateShuttleEvent createShuttle;
			CreateWorkerEvent createWorker;
			CreateJobEvent createJob;
			PlaceBuildingEvent placeBuilding;
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

		explicit GameCommand(const CreateShuttleEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::CreateShuttle),
			createShuttle(_event)
		{

		}

		explicit GameCommand(const CreateJobEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::CreateJob),
			createJob(_event)
		{

		}

		explicit GameCommand(const PlaceBuildingEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::PlaceBuilding),
			placeBuilding(_event)
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