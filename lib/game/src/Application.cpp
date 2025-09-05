#include <tokyo/Game/Application.hpp>

namespace tokyo
{

    bool Application::initialise(const sf::Vector2u& _resolution, const std::string& _name)
    {
        m_Name = _name;
        return initialise(sf::VideoMode(_resolution));
    }
    bool Application::initialise(const sf::VideoMode& _videoMode)
    {
        m_StartingMode = _videoMode;
        m_Initialised = true;

        bool isFullscreen = false; // TODO: Pass through fullscreen

        if (isFullscreen)
        {
            m_Window.create(_videoMode, m_Name, sf::State::Fullscreen);
        }
        else
        {
            m_Window.create(_videoMode, m_Name, sf::Style::Default, sf::State::Windowed);
            m_Window.setPosition(sf::Vector2i(
                sf::VideoMode::getDesktopMode().size.x * 0.5 - m_Window.getSize().x * 0.5,
                sf::VideoMode::getDesktopMode().size.y * 0.5 - m_Window.getSize().y * 0.5)
            );
        }

        setScene(nullptr);

        return true;
    }
    void Application::start()
    {
        if (!m_Initialised)
        {
            std::cerr << "Must initalise application before starting." << std::endl;
            return;
        }

        m_Running = true;

        m_Window.setVerticalSyncEnabled(true);

        sf::Clock clock{};
        const float delta = 1.0f / 60.0f;
        float accumulator = 0.0f;
        float statsAccumulator = 0.0f;
        unsigned int fps = 0;
        unsigned int ups = 0;
        while (m_Running)
        {
            float frameTime = clock.restart().asSeconds();
            if (frameTime > 0.5f)
            {
                frameTime = 0.5f;
            }

            accumulator += frameTime;

            statsAccumulator += frameTime;

            if (statsAccumulator >= 1.0f)
            {
                std::cout << "FPS: " << fps << " UPS: " << ups << std::endl;
                statsAccumulator -= 1.0f;
                fps = 0;
                ups = 0;
            }

            while (accumulator >= delta)
            {
                while (const std::optional event = m_Window.pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        stop();
                    }

                    if (event.has_value() && m_Scene != nullptr)
                    {
                        //m_Scene->handleEvent(event);
                    }
                }

                // Update
                update(delta);
                ups++;

                accumulator -= delta;
            }

            // Render
            render(m_Window, accumulator / delta);
            fps++;
        }

        m_Window.close();
    }
    void Application::stop()
    {
        m_Running = false;
    }

    bool Application::startSplash(const sf::VideoMode& _videoMode, Scene* _splashScene)
    {
        m_StartingMode = _videoMode;
        m_SplashShowing = true;

        auto splashVideoMode = _videoMode;

        splashVideoMode.size = {800, 400}; 

        m_Window.create(splashVideoMode, m_Name, sf::Style::None, sf::State::Windowed);

        setScene(_splashScene);

        return true;
    }
    void Application::renderSplash()
    {
        render(m_Window, 0.0f);
    }
    bool Application::splashFinished()
    {
        return splashFinished(m_StartingMode);
    }
    bool Application::splashFinished(const sf::VideoMode& _videoMode)
    {
        m_Window.clear();
        m_Window.display();

        bool isFullscreen = false; // TODO: Pass through fullscreen

        if (isFullscreen)
        {
            m_Window.create(_videoMode, m_Name, sf::State::Fullscreen);
        }
        else
        {
            m_Window.create(_videoMode, m_Name, sf::Style::Default, sf::State::Windowed);
            m_Window.setPosition(sf::Vector2i(
                sf::VideoMode::getDesktopMode().size.x * 0.5 - m_Window.getSize().x * 0.5,
                sf::VideoMode::getDesktopMode().size.y * 0.5 - m_Window.getSize().y * 0.5)
            );
        }

        setScene(nullptr);

        m_Initialised = true;

        return true;
    }

    void Application::setScene(Scene* _scene)
    {
        m_Scene = _scene;
    }

    sf::RenderWindow& Application::getWindow()
    {
        return m_Window;
    }
    const sf::RenderWindow& Application::getWindow() const
    {
        return m_Window;
    }

    void Application::update(float _delta)
    {
        if (m_Scene != nullptr)
        {
            m_Scene->UpdateScene(_delta);
        }
    }
    void Application::render(sf::RenderTarget& _target, float _alpha)
    {
        m_Window.clear();

        if (m_Scene != nullptr) 
        {

        }

        m_Window.display();
    }
}