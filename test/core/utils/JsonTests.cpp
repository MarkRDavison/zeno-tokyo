#include <catch2/catch_test_macros.hpp>
#include <tokyo/Core/Utils/Json.hpp>

namespace tokyo
{

    namespace Test
    {

        TEST_CASE("Sample json token detection works", "[Utility][Json]")
        {
            const std::string text = R"json(
{
    "menu": {
        "id": "file",
        "value" : "File",
        "popup" : {
            "menuitem": [
                { "value": "New", "onclick" : "CreateNewDoc()"},
                { "value": "Open", "onclick" : "OpenDoc()" },
                { "value": "Close", "onclick" : "CloseDoc()" },
                { "value": 55.5, "onclick" : "CloseDoc()" },
                { "value": 555, "onclick" : "CloseDoc()" },
                { "value": false, "onclick" : "CloseDoc()" },
                { "value": true, "onclick" : "CloseDoc()" }
            ]
        }
    }
})json";

            JsonDocument doc;

            std::vector<JsonToken> tokens;
            doc.tokenFound = [&](JsonToken _token) -> void
            {
                tokens.push_back(_token);
            };

            doc.parse(text);

            REQUIRE(91 == tokens.size());
        }

        TEST_CASE("Nested arrays work", "[Utility][Json]")
        {
            const std::string text = R"json([1, [2, [3], 2], 1])json";
            JsonDocument doc = Json::parseFromText(text);
            JsonNode& root = *doc.m_Root;

            {
                // root
                JsonNode& current = root;
                REQUIRE(current.name.empty());
                REQUIRE(JsonNode::Type::Array == current.type);
                REQUIRE(current.content.empty());
                REQUIRE(3 == current.children.size());

                {
                    // root[0]
                    JsonNode& current = root[0];
                    REQUIRE(current.name.empty());
                    REQUIRE(JsonNode::Type::ValueInteger == current.type);
                    REQUIRE("1" == current.content);
                    REQUIRE(1 == current.integer);
                    REQUIRE(current.children.empty());
                }
                {
                    // root[1]
                    JsonNode& current = root[1];
                    REQUIRE(current.name.empty());
                    REQUIRE(JsonNode::Type::Array == current.type);
                    REQUIRE(current.content.empty());
                    REQUIRE(3 == current.children.size());

                    {
                        // root[1][0]
                        JsonNode& current = root[1][0];
                        REQUIRE(current.name.empty());
                        REQUIRE(JsonNode::Type::ValueInteger == current.type);
                        REQUIRE("2" == current.content);
                        REQUIRE(2 == current.integer);
                        REQUIRE(current.children.empty());
                    }
                    {
                        // root[1][1]
                        JsonNode& current = root[1][1];
                        REQUIRE(current.name.empty());
                        REQUIRE(JsonNode::Type::Array == current.type);
                        REQUIRE(current.content.empty());
                        REQUIRE(1 == current.children.size());

                        {
                            // root[1][1][0]
                            JsonNode& current = root[1][1][0];
                            REQUIRE(current.name.empty());
                            REQUIRE(JsonNode::Type::ValueInteger == current.type);
                            REQUIRE("3" == current.content);
                            REQUIRE(3 == current.integer);
                            REQUIRE(current.children.empty());
                        }
                    }
                    {
                        // root[1][2]
                        JsonNode& current = root[1][2];
                        REQUIRE(current.name.empty());
                        REQUIRE(JsonNode::Type::ValueInteger == current.type);
                        REQUIRE("2" == current.content);
                        REQUIRE(2 == current.integer);
                        REQUIRE(current.children.empty());
                    }
                }
                {
                    // root[2]
                    JsonNode& current = root[2];
                    REQUIRE(current.name.empty());
                    REQUIRE(JsonNode::Type::ValueInteger == current.type);
                    REQUIRE("1" == current.content);
                    REQUIRE(1 == current.integer);
                    REQUIRE(current.children.empty());
                }
            }
        }

        TEST_CASE("Advent of code json examples work", "[Utility][Json]")
        {
            SECTION("Array inside an object")
            {
                const std::string text = R"json({"d":"red","e":[1,2,3.2,"4x4"],"f":5})json";

                JsonDocument doc = Json::parseFromText(text);
                JsonNode& root = *doc.m_Root;

                {
                    // Root Node
                    JsonNode& current = root;
                    REQUIRE(current.name.empty());
                    REQUIRE(JsonNode::Type::Object == current.type);
                    REQUIRE(current.content.empty());
                    REQUIRE(3 == current.children.size());

                    {
                        // d
                        JsonNode& current = root["d"];
                        REQUIRE("d" == current.name);
                        REQUIRE(JsonNode::Type::ValueString == current.type);
                        REQUIRE("red" == current.content);
                        REQUIRE(current.children.empty());
                    }
                    {
                        // e
                        JsonNode& current = root["e"];
                        REQUIRE("e" == current.name);
                        REQUIRE(JsonNode::Type::Array == current.type);
                        REQUIRE(current.content.empty());
                        REQUIRE(4 == current.children.size());

                        {
                            // e[0]
                            JsonNode& current = root["e"][0];
                            REQUIRE(current.name.empty());
                            REQUIRE(JsonNode::Type::ValueInteger == current.type);
                            REQUIRE("1" == current.content);
                            REQUIRE(1 == current.integer);
                            REQUIRE(current.children.empty());
                        }
                        {
                            // e[1]
                            JsonNode& current = root["e"][1];
                            REQUIRE(current.name.empty());
                            REQUIRE(JsonNode::Type::ValueInteger == current.type);
                            REQUIRE("2" == current.content);
                            REQUIRE(2 == current.integer);
                            REQUIRE(current.children.empty());
                        }
                        {
                            // e[2]
                            JsonNode& current = root["e"][2];
                            REQUIRE(current.name.empty());
                            REQUIRE(JsonNode::Type::ValueNumber == current.type);
                            REQUIRE("3.2" == current.content);
                            REQUIRE(3.2f == current.number);
                            REQUIRE(current.children.empty());
                        }
                        {
                            // e[3]
                            JsonNode& current = root["e"][3];
                            REQUIRE(current.name.empty());
                            REQUIRE(JsonNode::Type::ValueString == current.type);
                            REQUIRE("4x4" == current.content);
                            REQUIRE(current.children.empty());
                        }
                    }
                    {
                        // f
                        JsonNode& current = root["f"];
                        REQUIRE("f" == current.name);
                        REQUIRE(JsonNode::Type::ValueInteger == current.type);
                        REQUIRE("5" == current.content);
                        REQUIRE(5 == current.integer);
                        REQUIRE(current.children.empty());
                    }
                }
            }
        }

        TEST_CASE("Default streaming method creates json tree as expected", "[Utility][Json]")
        {
            const std::string text = R"json(
{
    "menu": {
        "id": "file",
        "value" : "File",
        "popup" : {
            "menuitem": [
                { "value": "New", "onclick" : "CreateNewDoc()"},
                { "value": 55.5, "onclick" : "CloseDoc()" },
                { "value": 555, "onclick" : "CloseDoc()" },
                { "value": true, "onclick" : "CloseDoc()" }
            ]
        }
    }
})json";
            JsonDocument doc = Json::parseFromText(text);
            JsonNode& root = *doc.m_Root;

            {
                // Root Node
                JsonNode& current = root;
                REQUIRE(current.name.empty());
                REQUIRE(JsonNode::Type::Object == current.type);
                REQUIRE(current.content.empty());
                REQUIRE(1 == current.children.size());

                {
                    // menu
                    JsonNode& current = root["menu"];
                    REQUIRE("menu" == current.name);
                    REQUIRE(JsonNode::Type::Object == current.type);
                    REQUIRE(current.content.empty());
                    REQUIRE(3 == current.children.size());

                    {
                        {
                            // menu/id
                            JsonNode& current = root["menu"]["id"];
                            REQUIRE("id" == current.name);
                            REQUIRE(JsonNode::Type::ValueString == current.type);
                            REQUIRE("file" == current.content);
                            REQUIRE(current.children.empty());
                        }
                        {
                            // menu/value
                            JsonNode& current = root["menu"]["value"];
                            REQUIRE("value" == current.name);
                            REQUIRE(JsonNode::Type::ValueString == current.type);
                            REQUIRE("File" == current.content);
                            REQUIRE(current.children.empty());
                        }
                        {
                            // menu/popup
                            JsonNode& current = root["menu"]["popup"];
                            REQUIRE("popup" == current.name);
                            REQUIRE(JsonNode::Type::Object == current.type);
                            REQUIRE(current.content.empty());
                            REQUIRE(1 == current.children.size());

                            {
                                // menu/popup/menuitem
                                JsonNode& current = root["menu"]["popup"]["menuitem"];
                                REQUIRE("menuitem" == current.name);
                                REQUIRE(JsonNode::Type::Array == current.type);
                                REQUIRE(current.content.empty());
                                REQUIRE(4 == current.children.size());

                                {
                                    // menu/popup/menuitem[0]
                                    JsonNode& current = root["menu"]["popup"]["menuitem"][0];
                                    REQUIRE(current.name.empty());
                                    REQUIRE(JsonNode::Type::Object == current.type);
                                    REQUIRE(current.content.empty());
                                    REQUIRE(2 == current.children.size());

                                    {
                                        // menu/popup/menuitem[0]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][0]["value"];
                                        REQUIRE("value" == current.name);
                                        REQUIRE(JsonNode::Type::ValueString == current.type);
                                        REQUIRE("New" == current.content);
                                        REQUIRE(current.children.empty());
                                    }
                                    {
                                        // menu/popup/menuitem[0]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][0]["onclick"];
                                        REQUIRE("onclick" == current.name);
                                        REQUIRE(JsonNode::Type::ValueString == current.type);
                                        REQUIRE("CreateNewDoc()" == current.content);
                                        REQUIRE(current.children.empty());
                                    }
                                }
                                {
                                    // menu/popup/menuitem[1]
                                    JsonNode& current = root["menu"]["popup"]["menuitem"][0];
                                    REQUIRE(current.name.empty());
                                    REQUIRE(JsonNode::Type::Object == current.type);
                                    REQUIRE(current.content.empty());
                                    REQUIRE(2 == current.children.size());

                                    {
                                        // menu/popup/menuitem[1]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][1]["value"];
                                        REQUIRE("value" == current.name);
                                        REQUIRE(JsonNode::Type::ValueNumber == current.type);
                                        REQUIRE("55.5" == current.content);
                                        REQUIRE(55.5 == current.number);
                                        REQUIRE(current.children.empty());
                                    }
                                    {
                                        // menu/popup/menuitem[1]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][1]["onclick"];
                                        REQUIRE("onclick" == current.name);
                                        REQUIRE(JsonNode::Type::ValueString == current.type);
                                        REQUIRE("CloseDoc()" == current.content);
                                        REQUIRE(current.children.empty());
                                    }
                                }
                                {
                                    // menu/popup/menuitem[2]
                                    JsonNode& current = root["menu"]["popup"]["menuitem"][0];
                                    REQUIRE(current.name.empty());
                                    REQUIRE(JsonNode::Type::Object == current.type);
                                    REQUIRE(current.content.empty());
                                    REQUIRE(2 == current.children.size());

                                    {
                                        // menu/popup/menuitem[1]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][2]["value"];
                                        REQUIRE("value" == current.name);
                                        REQUIRE(JsonNode::Type::ValueInteger == current.type);
                                        REQUIRE("555" == current.content);
                                        REQUIRE(555 == current.integer);
                                        REQUIRE(current.children.empty());
                                    }
                                    {
                                        // menu/popup/menuitem[1]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][2]["onclick"];
                                        REQUIRE("onclick" == current.name);
                                        REQUIRE(JsonNode::Type::ValueString == current.type);
                                        REQUIRE("CloseDoc()" == current.content);
                                        REQUIRE(current.children.empty());
                                    }
                                }
                                {
                                    // menu/popup/menuitem[3]
                                    JsonNode& current = root["menu"]["popup"]["menuitem"][0];
                                    REQUIRE(current.name.empty());
                                    REQUIRE(JsonNode::Type::Object == current.type);
                                    REQUIRE(current.content.empty());
                                    REQUIRE(2 == current.children.size());

                                    {
                                        // menu/popup/menuitem[1]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][3]["value"];
                                        REQUIRE("value" == current.name);
                                        REQUIRE(JsonNode::Type::ValueBoolean == current.type);
                                        REQUIRE("true" == current.content);
                                        REQUIRE(current.boolean);
                                        REQUIRE(current.children.empty());
                                    }
                                    {
                                        // menu/popup/menuitem[1]/value
                                        JsonNode& current = root["menu"]["popup"]["menuitem"][3]["onclick"];
                                        REQUIRE("onclick" == current.name);
                                        REQUIRE(JsonNode::Type::ValueString == current.type);
                                        REQUIRE("CloseDoc()" == current.content);
                                        REQUIRE(current.children.empty());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}