SET(MODULE_LIBS
	"Catch2::Catch2WithMain"
	"tokyo-core${LIB_EXTENSION_SHARED}"
	"tokyo-game${LIB_EXTENSION_SHARED}"
)

testsubmodule("game" "${MODULE_LIBS}")