#pragma once

#include <tokyo/Driller/Constants.hpp>
#include <tokyo/Core/Utils/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <tokyo/Game/Resource/Resource.hpp>

namespace drl
{

	struct GameCommand
	{

		struct DigShaftEvent
		{
			explicit DigShaftEvent(int _level) : level(_level) {}
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
			PlaceBuildingEvent(void) = default;
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

		struct AddResourceEvent
		{
			AddResourceEvent() {}
			AddResourceEvent(const tokyo::Resource& _resource) :
				resource(_resource)
			{
			}
			tokyo::Resource resource;
		};

		struct AddUpgradeEvent
		{
			AddUpgradeEvent(const std::string& _upgradeName, float _value) :
				upgradeId((IdType)tokyo::String::fnv1a_32(_upgradeName)),
				value(_value)
			{
			}

			AddUpgradeEvent(IdType _upgradeId, float _value) :
				upgradeId(_upgradeId),
				value(_value)
			{
			}

			IdType upgradeId;
			float value;
		};

		enum class CommandContext
		{
			DiggingShaft,
			DiggingTile,
			CreatingWorker,
			CreatingShuttle,
			CreatingJob,
			PlacingBuilding,
			AddResource,
			AddingUpgrade,

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
			DiggingShaft,
			DiggingTile,
			CreateShuttle,
			CreatingWorker,
			CreateJob,
			PlacingBuilding,
			AddResource,
			AddingUpgrade,

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
			AddResourceEvent addResource;
			AddUpgradeEvent addUpgrade;
		};

		GameCommand(const DigShaftEvent& _digShaft, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::DiggingShaft),
			digShaft(_digShaft)
		{

		}

		GameCommand(const DigTileEvent& _digTile, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::DiggingTile),
			digTile(_digTile)
		{

		}

		GameCommand(const CreateShuttleEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::CreateShuttle),
			createShuttle(_event)
		{

		}

		GameCommand(const CreateJobEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::CreateJob),
			createJob(_event)
		{

		}

		GameCommand(const PlaceBuildingEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::PlacingBuilding),
			placeBuilding(_event)
		{

		}

		GameCommand(const CreateWorkerEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::CreatingWorker),
			createWorker(_event)
		{

		}

		GameCommand(const AddResourceEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::AddResource),
			addResource(_event)
		{

		}

		GameCommand(const AddUpgradeEvent& _event, CommandContext context, CommandSource source) :
			commandContext(context),
			commandSource(source),
			type(EventType::AddingUpgrade),
			addUpgrade(_event)
		{

		}
	};

}