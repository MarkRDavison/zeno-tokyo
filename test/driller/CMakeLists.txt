SET(MODULE_LIBS
	"Catch2::Catch2WithMain"
	"tokyo-driller${LIB_EXTENSION_SHARED}"
)

testsubmodule("driller" "${MODULE_LIBS}")