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
			"CommandContext",
			{
				{"DigShaft", drl::GameCommand::CommandContext::DigShaft},
				{"Undefined", drl::GameCommand::CommandContext::Undefined},
			});

		_state.new_enum<drl::GameCommand::CommandSource>(
			"CommandSource",
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

		_state.new_usertype<drl::GameCommand>(
			"GameCommand",
			sol::constructors<
				drl::GameCommand(drl::GameCommand::DigShaftEvent, drl::GameCommand::CommandContext, drl::GameCommand::CommandSource)
			>(),
			"type", &drl::GameCommand::type
		);
	}
}