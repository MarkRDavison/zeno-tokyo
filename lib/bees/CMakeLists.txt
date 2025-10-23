SET(MODULE_LIBS
	SFML::Graphics
	"tokyo-core${LIB_EXTENSION_SHARED}"
	"tokyo-game${LIB_EXTENSION_SHARED}"
)

SET(INCLUDE_DIRS
	"${PROJECT_SOURCE_DIR}/lib/bees/include"
)

submodule("Bees" "${MODULE_LIBS}" "${INCLUDE_DIRS}")