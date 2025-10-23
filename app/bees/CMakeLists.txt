SET(MODULE_LIBS
	SFML::Graphics
	"tokyo-core${LIB_EXTENSION_SHARED}"
	"tokyo-game${LIB_EXTENSION_SHARED}"
	"tokyo-bees${LIB_EXTENSION_SHARED}"
)

FILE(GLOB_RECURSE CPP_FILES "*.cpp")

CONFIGURE_FILE(BeesConfig.hpp.in "${CMAKE_CURRENT_LIST_DIR}/BeesConfig.hpp")

tokyoApplication("TokyoBees" "${CPP_FILES}" "${MODULE_LIBS}")