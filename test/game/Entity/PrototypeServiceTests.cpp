#include <catch2/catch_test_macros.hpp>
#include <tokyo/Game/Entity/PrototypeService.hpp>
#include <functional>

namespace tokyo
{
	namespace test
	{
		struct TestPrototype
		{
			int prototypeId;
		};

		struct TestEntity
		{

		};

		class TestPrototypeService : public tokyo::PrototypeService<TestPrototype, TestEntity, int>
		{
		public:
			TestPrototypeService(
				tokyo::IdentificationService<int>& idService
			) : 
				tokyo::PrototypeService<TestPrototype, TestEntity, int>(idService)
			{

			}

			TestEntity createInstance(const TestPrototype& _prototype) const override
			{
				if (createInstanceCallback)
				{
					return createInstanceCallback(_prototype);
				}

				return {};
			}

			std::function<TestEntity(const TestPrototype&)> createInstanceCallback;
		};

		using TestPrototypeServiceBase = tokyo::PrototypeService<TestPrototype, TestEntity, int>;

		TEST_CASE("isPrototypeRegistered returns false when no prototypes registered", "[PrototypeService]")
		{
			tokyo::IdentificationService<int> idService;
			TestPrototypeService prototypeService(idService);

			const std::string prototypeName = "Some Prototype Name";

			const int prototypeId = tokyo::String::fnv1a_32(prototypeName);

			REQUIRE_FALSE(prototypeService.isPrototypeRegistered(prototypeName));
			REQUIRE_FALSE(prototypeService.isPrototypeRegistered(prototypeId));
		}

		TEST_CASE("isPrototypeRegistered returns true when prototype registered", "[PrototypeService]")
		{
			tokyo::IdentificationService<int> idService;
			TestPrototypeService prototypeService(idService);

			const std::string prototypeName = "Some Prototype Name";

			const int prototypeId = tokyo::String::fnv1a_32(prototypeName);

			TestPrototype prototype = { .prototypeId = prototypeId };

			prototypeService.registerPrototype(prototypeId, prototype);

			REQUIRE(prototypeService.isPrototypeRegistered(prototypeName));
			REQUIRE(prototypeService.isPrototypeRegistered(prototypeId));
		}

		TEST_CASE("getPrototype throws when prototype not registered", "[PrototypeService]")
		{
			tokyo::IdentificationService<int> idService;
			TestPrototypeService prototypeService(idService);

			const std::string prototypeName = "Some Prototype Name";

			const int prototypeId = tokyo::String::fnv1a_32(prototypeName);

			TestPrototype prototype = { .prototypeId = prototypeId };

			REQUIRE_THROWS_AS(prototypeService.getPrototype(prototypeName), std::logic_error);
			REQUIRE_THROWS_AS(prototypeService.getPrototype(prototypeId), std::logic_error);
		}

		TEST_CASE("getPrototype returns the prototype when prototype registered", "[PrototypeService]")
		{
			tokyo::IdentificationService<int> idService;
			TestPrototypeService prototypeService(idService);

			const std::string prototypeName = "Some Prototype Name";

			const int prototypeId = tokyo::String::fnv1a_32(prototypeName);

			TestPrototype prototype = { .prototypeId = prototypeId };

			prototypeService.registerPrototype(prototypeId, prototype);

			REQUIRE(prototypeId == prototypeService.getPrototype(prototypeName).prototypeId);
			REQUIRE(prototypeId == prototypeService.getPrototype(prototypeId).prototypeId);
		}

		TEST_CASE("getPrototype calls expected overridden method with expected prototype", "[PrototypeService]")
		{
			tokyo::IdentificationService<int> idService;
			TestPrototypeService prototypeService(idService);

			const std::string prototypeName = "Some Prototype Name";

			const int prototypeId = tokyo::String::fnv1a_32(prototypeName);

			TestPrototype prototype = { .prototypeId = prototypeId };

			prototypeService.registerPrototype(prototypeId, prototype);

			auto callbackInvoked = false;

			prototypeService.createInstanceCallback = 
				[&](const TestPrototype& _retrievedPrototype) -> TestEntity 
				{
					REQUIRE(prototypeId == _retrievedPrototype.prototypeId);

					callbackInvoked = true;
					return {};
				};

			prototypeService.TestPrototypeServiceBase::createInstanceById(prototypeId);
			
			REQUIRE(callbackInvoked);
		}
	}
}