#include <tokyo/Driller/Scripting/CoreUserData.hpp>
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
	}
}