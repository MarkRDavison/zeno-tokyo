#include <tokyo/Driller/Scripting/CoreUserData.hpp>
#include <tokyo/Driller/Core/GameCommand.hpp>
#include <SFML/System/Vector2.hpp>
#include <sol/sol.hpp>

namespace drl
{
	void CoreUserData::generateInfrastructureUserData(sol::state& _state)
	{
		_state.new_usertype<sf::Vector2i>(
			"vec2i",
			sol::constructors<
				sf::Vector2i(int, int)
			>(),
			"x", &sf::Vector2i::x,
			"y", &sf::Vector2i::y,
			sol::meta_function::addition, std::plus<sf::Vector2i>(),
			sol::meta_function::subtraction, std::minus<sf::Vector2i>()
		);

		_state.new_usertype<sf::Vector2f>(
			"vec2f",
			sol::constructors<
				sf::Vector2f(float, float)
			>(),
			"x", &sf::Vector2f::x,
			"y", &sf::Vector2f::y,
			sol::meta_function::addition, std::plus<sf::Vector2f>(),
			sol::meta_function::subtraction, std::minus<sf::Vector2f>()
		);

		_state.new_enum<drl::GameCommand::CommandContext>(
			"GameCommandContext",
			{
				{"DigShaft", drl::GameCommand::CommandContext::DigShaft},
				{"DigTile", drl::GameCommand::CommandContext::DigTile},
				{"CreateWorker", drl::GameCommand::CommandContext::CreateWorker},
				{"CreatingShuttle", drl::GameCommand::CommandContext::CreatingShuttle},
				{"CreatingWorker", drl::GameCommand::CommandContext::CreatingWorker},
				{"CreatingJob", drl::GameCommand::CommandContext::CreatingJob},
				{"Undefined", drl::GameCommand::CommandContext::Undefined},
			});

		_state.new_enum<drl::GameCommand::CommandSource>(
			"GameCommandSource",
			{
				{"Setup", drl::GameCommand::CommandSource::Setup},
				{"Player", drl::GameCommand::CommandSource::Player},
				{"System", drl::GameCommand::CommandSource::System}
			});

		_state.new_usertype<drl::GameCommand::DigShaftEvent>(
			"DigShaftEvent",
			sol::constructors<
				drl::GameCommand::DigShaftEvent(int)
			>(),
			"level", &drl::GameCommand::DigShaftEvent::level
		);

		_state.new_usertype<drl::GameCommand::DigTileEvent>(
			"DigTileEvent",
			sol::constructors<
			drl::GameCommand::DigTileEvent(int, int)
			>(),
			"level", &drl::GameCommand::DigTileEvent::level,
			"column", &drl::GameCommand::DigTileEvent::column
		);

		_state.new_usertype<drl::GameCommand::PlaceBuildingEvent>(
			"PlaceBuildingEvent",
			sol::constructors<
				drl::GameCommand::PlaceBuildingEvent(std::string, int, int),
				drl::GameCommand::PlaceBuildingEvent(IdType, int, int)
			>(),
			"prototypeId", &drl::GameCommand::PlaceBuildingEvent::prototypeId,
			"level", &drl::GameCommand::PlaceBuildingEvent::level,
			"column", &drl::GameCommand::PlaceBuildingEvent::column
		);

		_state.new_usertype<drl::GameCommand::CreateShuttleEvent>(
			"CreateShuttleEvent",
			sol::constructors<
				drl::GameCommand::CreateShuttleEvent(std::string)
			>(),
			"prototypeId", &drl::GameCommand::CreateShuttleEvent::prototypeId
		);

		_state.new_usertype<drl::GameCommand::CreateWorkerEvent>(
			"CreateWorkerEvent",
			sol::constructors<
				drl::GameCommand::CreateWorkerEvent(const std::string&, sf::Vector2f)
			>(),
			"prototypeId", &drl::GameCommand::CreateWorkerEvent::prototypeId,
			"coordinates", &drl::GameCommand::CreateWorkerEvent::coordinates
		);

		_state.new_usertype<drl::GameCommand::CreateJobEvent>(
			"CreateJobEvent",
			sol::constructors<
				drl::GameCommand::CreateJobEvent(std::string,std::string, sf::Vector2i)
			>(),
			"prototypeId", &drl::GameCommand::CreateJobEvent::prototypeId,
			"additionalPrototypeId", &drl::GameCommand::CreateJobEvent::additionalPrototypeId,
			"coordinates", &drl::GameCommand::CreateJobEvent::coordinates
		);

		_state.new_usertype<drl::GameCommand>(
			"GameCommand",
			sol::constructors<
				drl::GameCommand(drl::GameCommand::DigShaftEvent, drl::GameCommand::CommandContext, drl::GameCommand::CommandSource),
				drl::GameCommand(drl::GameCommand::DigTileEvent, drl::GameCommand::CommandContext, drl::GameCommand::CommandSource),
				drl::GameCommand(drl::GameCommand::PlaceBuildingEvent, drl::GameCommand::CommandContext, drl::GameCommand::CommandSource),
				drl::GameCommand(drl::GameCommand::CreateShuttleEvent, drl::GameCommand::CommandContext, drl::GameCommand::CommandSource),
				drl::GameCommand(drl::GameCommand::CreateWorkerEvent, drl::GameCommand::CommandContext, drl::GameCommand::CommandSource),
				drl::GameCommand(drl::GameCommand::CreateJobEvent, drl::GameCommand::CommandContext, drl::GameCommand::CommandSource)
			>(),
			"type", &drl::GameCommand::type
		);
	}
}