SET(MODULE_LIBS
	"tokyo-driller${LIB_EXTENSION_SHARED}"
)

FILE(GLOB_RECURSE CPP_FILES "*.cpp")

tokyoApplication("TokyoDriller" "${CPP_FILES}" "${MODULE_LIBS}")