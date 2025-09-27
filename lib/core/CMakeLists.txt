SET(MODULE_LIBS
	lua_library
	sol2::sol2
	SFML::Graphics
)

SET(INCLUDE_DIRS
	"${PROJECT_SOURCE_DIR}/lib/core/include"
)

submodule("Core" "${MODULE_LIBS}" "${INCLUDE_DIRS}")