#include <catch2/catch_test_macros.hpp>
#include <tokyo/Game/Resource/ResourceService.hpp>

constexpr const char* RESOURCE_1{ "Lives" };
constexpr const char* RESOURCE_2{ "Gold" };
constexpr const char* RESOURCE_3{ "Deaths" };

namespace tokyo
{
	namespace test
	{
		struct Package
		{
			ResourceService service;
		};

		TEST_CASE("Requesting the value of a new resource returns 0", "[Resource][ResourceService]")
		{
			Package package{};

			REQUIRE(0 == package.service.getResource(RESOURCE_1));
		}

		TEST_CASE("Setting a value of a new resource then requesting it returns the expected value", "[Resource][ResourceService]")
		{
			const int ResourceValue = 12;

			Package package{};
			package.service.setResource(RESOURCE_1, ResourceValue);

			REQUIRE(ResourceValue == package.service.getResource(RESOURCE_1));
		}

		TEST_CASE("Updating a new resources value sets it to the expected value", "[Resource][ResourceService]")
		{
			const int ResourceValue = 12;

			Package package{};
			package.service.updateResource(RESOURCE_1, ResourceValue);

			REQUIRE(ResourceValue == package.service.getResource(RESOURCE_1));
		}

		TEST_CASE("Updating an existing resource increases its value by the expected amount", "[Resource][ResourceService]")
		{
			const int StartResourceValue = 12;
			const int UpdateResourceValue = 78;

			Package package{};
			package.service.setResource(RESOURCE_1, StartResourceValue);
			package.service.updateResource(RESOURCE_1, UpdateResourceValue);

			REQUIRE(StartResourceValue + UpdateResourceValue == package.service.getResource(RESOURCE_1));
		}

		TEST_CASE("Setting a value of a new resource cant set it past the max once set", "[Resource][ResourceService]")
		{
			const int ResourceValue = 78;
			const int MaxResourceValue = 12;

			Package package{};
			package.service.setResourceMaximum(RESOURCE_1, MaxResourceValue);

			package.service.setResource(RESOURCE_1, ResourceValue);

			REQUIRE(ResourceValue > MaxResourceValue);
			REQUIRE(MaxResourceValue == package.service.getResource(RESOURCE_1));
		}

		TEST_CASE("Updating a value of an existing resource cant set it past the max once set", "[Resource][ResourceService]")
		{
			const int StartResourceValue = 12;
			const int UpdateResourceValue = 96;
			const int MaxResourceValue = 78;

			Package package{};
			package.service.setResourceMaximum(RESOURCE_1, MaxResourceValue);
			package.service.setResource(RESOURCE_1, StartResourceValue);
			package.service.updateResource(RESOURCE_1, UpdateResourceValue);

			REQUIRE(StartResourceValue + UpdateResourceValue > MaxResourceValue);
			REQUIRE(MaxResourceValue == package.service.getResource(RESOURCE_1));
		}

		TEST_CASE("Setting the value of a new resource notifies its value has been changed", "[Resource][ResourceService]")
		{
			const std::string ResourceName = RESOURCE_1;
			bool resourceChangedInvoked{ false };
			Package package{};
			package.service.resourceChanged.registerCallback(
				[&](ResourceId _id)
				{
					resourceChangedInvoked = true;
					REQUIRE(tokyo::String::fnv1a_32(ResourceName) == _id);
				});

			package.service.setResource(ResourceName, 10);

			REQUIRE(resourceChangedInvoked);
		}

		TEST_CASE("Setting the value of an existing resource notifies its value has been changed", "[Resource][ResourceService]")
		{
			bool resourceChangedInvoked{ false };
			const std::string ResourceName = RESOURCE_1;
			Package package{};
			package.service.resourceChanged.registerCallback(
				[&](ResourceId _id)
				{
					resourceChangedInvoked = true;
					REQUIRE(tokyo::String::fnv1a_32(ResourceName) == _id);
				});
			package.service.updateResource(ResourceName, 10);

			REQUIRE(resourceChangedInvoked);
		}

		TEST_CASE("empty resource service can afford empty resource bundle", "[Resource][ResourceService]")
		{
			Package package{};

			REQUIRE(package.service.canAfford(ResourceBundle()));
		}

		TEST_CASE("empty resource service can afford resource bundle with resources of zero amount", "[Resource][ResourceService]")
		{
			Package package{};

			ResourceBundle bundle{};
			Resource resource{};
			resource.id = tokyo::String::fnv1a_32(RESOURCE_2);
			resource.amount = 0;
			bundle.push_back(resource);

			REQUIRE(package.service.canAfford(bundle));
		}

		TEST_CASE("empty resource service cannot afford resource bundle with a single resource with > 0 amount", "[Resource][ResourceService]")
		{
			Package package{};

			ResourceBundle bundle{};
			Resource resource{};
			resource.id = tokyo::String::fnv1a_32(RESOURCE_2);
			resource.amount = 1;
			bundle.push_back(resource);

			REQUIRE_FALSE(package.service.canAfford(bundle));
		}

		TEST_CASE("resource service with single resource of large amount can afford resource bundle with a single resource with > 0 amount", "[Resource][ResourceService]")
		{
			Package package{};

			package.service.setResource(RESOURCE_2, 50);

			ResourceBundle bundle{};
			Resource resource{};
			resource.id = tokyo::String::fnv1a_32(RESOURCE_2);
			resource.amount = 1;
			bundle.push_back(resource);

			REQUIRE(package.service.canAfford(bundle));
		}

		TEST_CASE("resource service with single resource of large amount cannot afford resource bundle with multiple resource with > 0 amount", "[Resource][ResourceService]")
		{
			Package package{};

			package.service.setResource(RESOURCE_2, 50);

			ResourceBundle bundle{};
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_2);
				resource.amount = 1;
				bundle.push_back(resource);
			}
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_3);
				resource.amount = 1;
				bundle.push_back(resource);
			}

			REQUIRE_FALSE(package.service.canAfford(bundle));
		}

		TEST_CASE("resource service with multiple resource of large amount can afford resource bundle with multiple resource with > 0 amount", "[Resource][ResourceService]")
		{
			Package package{};

			package.service.setResource(RESOURCE_2, 50);
			package.service.setResource(RESOURCE_3, 50);

			ResourceBundle bundle{};
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_2);
				resource.amount = 1;
				bundle.push_back(resource);
			}
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_3);
				resource.amount = 1;
				bundle.push_back(resource);
			}

			REQUIRE(package.service.canAfford(bundle));
		}

		TEST_CASE("Paying a resource bundle reduces all relevant resources", "[Resource][ResourceService]")
		{
			const int StartingAmount = 50;
			const int Gold1PayAmount = 12;
			const int Gold2PayAmount = 22;
			Package package{};

			package.service.setResource(RESOURCE_2, StartingAmount);
			package.service.setResource(RESOURCE_3, StartingAmount);

			ResourceBundle bundle{};
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_2);
				resource.amount = Gold1PayAmount;
				bundle.push_back(resource);
			}
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_3);
				resource.amount = Gold2PayAmount;
				bundle.push_back(resource);
			}

			package.service.payResourceBundle(bundle);

			REQUIRE(StartingAmount - Gold1PayAmount == package.service.getResource(RESOURCE_2));
			REQUIRE(StartingAmount - Gold2PayAmount == package.service.getResource(RESOURCE_3));
		}

		TEST_CASE("Receiving a resource bundle increases all relevant resources", "[Resource][ResourceService]")
		{
			const int StartingAmount = 50;
			const int Gold1PayAmount = 12;
			const int Gold2PayAmount = 22;
			Package package{};

			package.service.setResource(RESOURCE_2, StartingAmount);
			package.service.setResource(RESOURCE_3, StartingAmount);

			ResourceBundle bundle{};
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_2);
				resource.amount = Gold1PayAmount;
				bundle.push_back(resource);
			}
			{
				Resource resource{};
				resource.id = tokyo::String::fnv1a_32(RESOURCE_3);
				resource.amount = Gold2PayAmount;
				bundle.push_back(resource);
			}

			package.service.receiveResourceBundle(bundle);

			REQUIRE(StartingAmount + Gold1PayAmount == package.service.getResource(RESOURCE_2));
			REQUIRE(StartingAmount + Gold2PayAmount == package.service.getResource(RESOURCE_3));
		}
	}
}