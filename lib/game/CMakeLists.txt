SET(MODULE_LIBS
	SFML::Graphics
)

SET(INCLUDE_DIRS
	"${PROJECT_SOURCE_DIR}/lib/core/include"
	"${PROJECT_SOURCE_DIR}/lib/game/include"
)

submodule("Game" "${MODULE_LIBS}" "${INCLUDE_DIRS}")