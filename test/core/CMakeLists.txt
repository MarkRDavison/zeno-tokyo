SET(MODULE_LIBS
	"Catch2::Catch2WithMain"
	"tokyo-core${LIB_EXTENSION_SHARED}"
)

testsubmodule("core" "${MODULE_LIBS}")