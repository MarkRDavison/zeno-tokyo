SET(MODULE_LIBS
	"tokyo-driller${LIB_EXTENSION_SHARED}"
)


FILE(GLOB_RECURSE CPP_FILES "*.cpp")

CONFIGURE_FILE( DrillerConfig.hpp.in "${CMAKE_CURRENT_LIST_DIR}/DrillerConfig.hpp")

tokyoApplication("TokyoDriller" "${CPP_FILES}" "${MODULE_LIBS}")