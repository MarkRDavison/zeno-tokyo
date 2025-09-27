#include <tokyo/Driller/Scripting/PrototypeParser.hpp>
#include <tokyo/Driller/Scripting/ScriptingConstants.hpp>
#include <sol/sol.hpp>

namespace drl
{

	ParsedPrototypes PrototypeParser::parse(sol::state& _state) const
	{
		ParsedPrototypes p{};

		const sol::table& jobs = _state[ScriptingConstants::Prototypes_ScriptRoot][ScriptingConstants::Prototypes_Jobs_ScriptRoot];
		for (const auto& kv : jobs)
		{
			auto& jp = p.jobPrototypes.emplace_back();
			const sol::table table = kv.second;
			jp.name = table["name"].get<std::string>();
			jp.repeats = table["repeats"].get<bool>();
			jp.work = table["work"].get<float>();
			jp.onComplete = table["onComplete"].get<std::function<void(JobInstance)>>();
			jp.calculateOffset = table["calculateOffset"].get_or<std::function<sf::Vector2f(JobInstance, JobPrototype)>>({});
		}

		const sol::table& workers = _state[ScriptingConstants::Prototypes_ScriptRoot][ScriptingConstants::Prototypes_Workers_ScriptRoot];
		for (const auto& kv : workers)
		{
			const sol::table table = kv.second;
			auto& wp = p.workerPrototypes.emplace_back();
			wp.name = table["name"].get<std::string>();
			wp.validJobPrototypes = table["jobs"].get<std::unordered_set<std::string>>();
		}

		const sol::table& shuttles = _state[ScriptingConstants::Prototypes_ScriptRoot][ScriptingConstants::Prototypes_Shuttles_ScriptRoot];
		for (const auto& kv : shuttles)
		{
			const sol::table table = kv.second;
			auto& sp = p.shuttlePrototypes.emplace_back();
			sp.name = table["name"].get<std::string>();
			sp.size = {
				table["size"]["x"].get<int>(),
				table["size"]["y"].get<int>()
			};
			sp.texture = {
				table["texture"]["x"].get<int>(),
				table["texture"]["y"].get<int>()
			};
			sp.idleTime = table["idleTime"].get<float>();
			sp.loadingTime = table["loadingTime"].get<float>();
			sp.speed = table["speed"].get<float>();
			sp.allowedCargo = table["allowedCargo"].get<std::unordered_set<std::string>>();
		}

		const sol::table& buildings = _state[ScriptingConstants::Prototypes_ScriptRoot][ScriptingConstants::Prototypes_Buildings_ScriptRoot];
		for (const auto& kv : buildings)
		{
			const sol::table table = kv.second;
			auto& bp = p.buildingPrototypes.emplace_back();
			bp.name = table["name"].get<std::string>();
			bp.size = {
				table["size"]["x"].get<int>(),
				table["size"]["y"].get<int>()
			};
			bp.texture = {
				table["texture"]["x"].get<int>(),
				table["texture"]["y"].get<int>()
			};
			const sol::table& bw = table["workers"];
			for (const auto& bwkv : bw)
			{
				const sol::table bwt = bwkv.second;
				bp.requiredWorkers[bwt["name"].get<std::string>()] = bwt["amount"].get<int>();
			}
			const sol::optional<sol::table>& obj = table["jobs"];
			if (obj.has_value())
			{
				const auto& bj = obj.value();
				for (const auto& bjkv : bj)
				{
					const sol::table bjt = bjkv.second;
					const sf::Vector2f bjOffset = {
						bjt["offset"]["x"].get<float>(),
						bjt["offset"]["y"].get<float>()
					};
					bp.providedJobs.emplace_back(bjt["name"].get<std::string>(), bjOffset);
				}
			}
		}

		return p;
	}

}