SET(MODULE_LIBS
	"tokyo-platformer${LIB_EXTENSION_SHARED}"
)


FILE(GLOB_RECURSE CPP_FILES "*.cpp")

CONFIGURE_FILE( PlatformerConfig.hpp.in "${CMAKE_CURRENT_LIST_DIR}/PlatformerConfig.hpp")

tokyoApplication("TokyoPlatformer" "${CPP_FILES}" "${MODULE_LIBS}")