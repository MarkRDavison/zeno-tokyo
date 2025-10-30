#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <optional>
#include <iostream>

#define CLAY_IMPLEMENTATION
#include "clay.h"

const Clay_Color COLOR_LIGHT = Clay_Color{ 224, 215, 210, 255 };
const Clay_Color COLOR_RED = Clay_Color{ 168, 66, 28, 255 };
const Clay_Color COLOR_ORANGE = Clay_Color{ 225, 138, 50, 255 };

void HandleClayErrors(Clay_ErrorData errorData)
{
    // See the Clay_ErrorData struct for more information
    printf("%s", errorData.errorText.chars);
    switch (errorData.errorType)
    {
        // etc
    }
}

static inline Clay_Dimensions MeasureText(Clay_StringSlice text, Clay_TextElementConfig* config, void* userData)
{
    // Clay_TextElementConfig contains members such as fontId, fontSize, letterSpacing etc
    // Note: Clay_String->chars is not guaranteed to be null terminated
    return Clay_Dimensions
    {
        .width = (float)text.length * config->fontSize, // <- this will only work for monospace fonts, see the renderers/ directory for more advanced text measurement
        .height = (float)config->fontSize
    };
}

// Layout config is just a struct that can be declared statically, or inline
Clay_ElementDeclaration sidebarItemConfig = Clay_ElementDeclaration
{
    .layout = {
        .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(50) }
    },
    .backgroundColor = COLOR_ORANGE
};

void SidebarItemComponent(int i)
{
    CLAY(CLAY_IDI("sidebar", i), sidebarItemConfig)
    {
        // children go here...
    }
}

int main(int, char**)
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Tokyo Ui Playground");

    // Note: malloc is only used here as an example, any allocator that provides
   // a pointer to addressable memory of at least totalMemorySize will work
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

    // Note: screenWidth and screenHeight will need to come from your environment, Clay doesn't handle window related tasks
    Clay_Initialize(arena, Clay_Dimensions { 1920, 1080 }, Clay_ErrorHandler{ HandleClayErrors });
    Clay_SetMeasureTextFunction(MeasureText, nullptr);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (auto* resized = event->getIf<sf::Event::Resized>())
            {
                window.setView(sf::View(sf::FloatRect({}, sf::Vector2f(resized->size))));
                // Optional: Update internal layout dimensions to support resizing
                Clay_SetLayoutDimensions(Clay_Dimensions{ (float)resized->size.x , (float)resized->size.y });
            }
        }

        auto delta = clock.restart().asSeconds();

        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling & debug tools
        //Clay_SetPointerState((Clay_Vector2) { mousePositionX, mousePositionY }, isMouseDown);
        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling and debug tools
        //Clay_UpdateScrollContainers(true, Clay_Vector2 { mouseWheelX, mouseWheelY }, delta);

        // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
        Clay_BeginLayout();
        
        CLAY(CLAY_ID("OuterContainer"), 
            { 
                .layout = {
                    .sizing = {
                        CLAY_SIZING_GROW(0), 
                        CLAY_SIZING_GROW(0)
                    }, 
                    .padding = CLAY_PADDING_ALL(16), 
                    .childGap = 16 
                }, 
                .backgroundColor = { 250,250,255,255} 
            })
        {
            CLAY(CLAY_ID("SideBar"), 
                {
                    .layout = {
                        .sizing = {
                            .width = CLAY_SIZING_FIXED(300), 
                            .height = CLAY_SIZING_GROW(0)
                        },
                        .padding = CLAY_PADDING_ALL(16), 
                        .childGap = 16,
                        .layoutDirection = CLAY_TOP_TO_BOTTOM
                    },
                    .backgroundColor = COLOR_LIGHT
                })
            {
                CLAY(CLAY_ID("ProfilePictureOuter"), 
                    { 
                        .layout = {
                            .sizing = {
                                .width = CLAY_SIZING_GROW(0) 
                            }, 
                            .padding = CLAY_PADDING_ALL(16), 
                            .childGap = 16, 
                            .childAlignment = {
                                .y = CLAY_ALIGN_Y_CENTER 
                            } 
                        }, 
                        .backgroundColor = COLOR_RED 
                    })
                {
                    CLAY(CLAY_ID("ProfilePicture"), 
                        { 
                            .layout = {
                                .sizing = {
                                    .width = CLAY_SIZING_FIXED(60), 
                                    .height = CLAY_SIZING_FIXED(60) 
                                }
                            }, 
                            .image = {
                                .imageData = nullptr
                            } 
                        }) 
                    {
                    }
                    CLAY_TEXT(CLAY_STRING("Clay"), CLAY_TEXT_CONFIG(
                        {
                            .textColor = {255, 255, 255, 255},
                            .fontSize = 24
                        }));
                }

                for (int i = 0; i < 5; i++)
                {
                    SidebarItemComponent(i);
                }
            }

            CLAY(CLAY_ID("MainContent"),
                {
                    .layout = {
                        .sizing = {
                            .width = CLAY_SIZING_GROW(0),
                            .height = CLAY_SIZING_GROW(0)
                        }
                    },
                    .backgroundColor = {0, 55, 0, 255}
                })
            {

            }

        }

        auto render = Clay_EndLayout();

        window.clear(sf::Color::Black);

        for (int i = 0; i < render.length; ++i)
        {
            auto cmd = Clay_RenderCommandArray_Get(&render, i);

            auto col = sf::Color(
                cmd->renderData.rectangle.backgroundColor.r,
                cmd->renderData.rectangle.backgroundColor.g,
                cmd->renderData.rectangle.backgroundColor.b,
                cmd->renderData.rectangle.backgroundColor.a);

            switch (cmd->commandType)
            {
            case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
                {
                    sf::RectangleShape r(sf::Vector2f(cmd->boundingBox.width, cmd->boundingBox.height));
                    r.setPosition({ cmd->boundingBox.x , cmd->boundingBox.y });
                    r.setFillColor(col);

                    window.draw(r);
                }
                break;
            case CLAY_RENDER_COMMAND_TYPE_BORDER:
                break;
            case CLAY_RENDER_COMMAND_TYPE_TEXT:
                std::cout << "Render: " << cmd->renderData.text.stringContents.chars << std::endl;
                break;
            case CLAY_RENDER_COMMAND_TYPE_IMAGE:
                break;
            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START:
                break;
            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END:
                break;
            }

        }


        window.display();
    }

    return 0;
}
