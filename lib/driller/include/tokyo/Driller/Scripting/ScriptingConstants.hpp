#pragma once

namespace drl
{

	class ScriptingConstants
	{
		ScriptingConstants() = delete;
		~ScriptingConstants() = delete;
	public:
		static constexpr const char Prototypes_ScriptRoot[] = "prototypes";
		static constexpr const char Prototypes_Shuttles_ScriptRoot[] = "shuttles";
		static constexpr const char Prototypes_Workers_ScriptRoot[] = "workers";
		static constexpr const char Prototypes_Jobs_ScriptRoot[] = "jobs";
		static constexpr const char Prototypes_Buildings_ScriptRoot[] = "buildings";
		static constexpr const char Resources_ScriptRoot[] = "resources";
	};

}