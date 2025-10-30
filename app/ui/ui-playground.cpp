#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <tokyo/Game/Ui/UiMaster.hpp>
#include <tokyo/Game/Ui/UiConstraints.hpp>
#include <tokyo/Game/Ui/Components/UiPanel.hpp>
#include <tokyo/Game/Ui/Constraints/PixelConstraint.hpp>
#include <tokyo/Game/Ui/Constraints/FillConstraint.hpp>
#include <tokyo/Game/Ui/Constraints/CenterConstraint.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Tokyo Ui Playground");

    auto uiMaster = tokyo::UiMaster::Get();

    uiMaster->init(800, 600, 1.0f);

    uiMaster->setMinDisplaySize(640, 480);

    //uiMaster->getContainer()->add(
    //    new tokyo::UiPanel(), 
    //    new tokyo::UiConstraints(
    //        new tokyo::PixelConstraint(16),
    //        new tokyo::PixelConstraint(16),
    //        new tokyo::FillConstraint(64),
    //        new tokyo::FillConstraint(64)));

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (auto resizedEvent = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({}, sf::Vector2f(resizedEvent->size));
                window.setView(sf::View(visibleArea));
                uiMaster->notifyScreenSizeChange(resizedEvent->size.x, resizedEvent->size.y);
            }
        }

        auto delta = clock.restart().asSeconds();

        uiMaster->update(delta);

        window.clear(sf::Color::Black);

        uiMaster->draw(window, sf::RenderStates::Default);

        window.display();
    }

    uiMaster->cleanup();

    return EXIT_SUCCESS;
}