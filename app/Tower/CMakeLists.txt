SET(MODULE_LIBS
	SFML::Graphics
	"tokyo-core${LIB_EXTENSION_SHARED}"
	"tokyo-game${LIB_EXTENSION_SHARED}"
)

FILE(GLOB_RECURSE CPP_FILES "*.cpp")

tokyoApplication("TokyoTower" "${CPP_FILES}" "${MODULE_LIBS}")