#pragma once 

#include <SFML/Graphics.hpp>
#include <tokyo/Game/Scene.hpp>

namespace tokyo
{

    class Application
    {
    public:
        Application() = default;
        Application(const Application& _other) = delete;
        Application(Application&& _other) noexcept = delete;
        Application& operator=(const Application& _other) = delete;
        Application& operator=(Application&& _other) noexcept = delete;

        void setName(const std::string& _name);
        bool initialise(const sf::Vector2u& _resolution, const std::string& _name);
        bool initialise(const sf::VideoMode& _videoMode);
        void start();
        void stop();

        bool startSplash(const sf::VideoMode& _videoMode, Scene* _splashScene);
        void renderSplash();
        bool splashFinished();
        bool splashFinished(const sf::VideoMode& _videoMode);

        void setScene(Scene* _scene);

        sf::RenderWindow& getWindow();
        const sf::RenderWindow& getWindow() const;

        void setAppSpeedMultiplier(float _multiplier);

    private:
        void update(float _delta);
        void render(sf::RenderTarget& _target);

    private:
        bool m_Running{ false };
        bool m_Initialised{ false };
        bool m_SplashShowing{ false };
        sf::VideoMode m_StartingMode;

        sf::RenderWindow m_Window;
        Scene* m_Scene{ nullptr };
        std::string m_Name;
        float m_Multiplier{ 1.0f };
    };
}