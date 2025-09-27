#pragma once

#include <unordered_map>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <tokyo/Core/Infrastructure/FileManager.hpp>
#include <SFML/Graphics/Font.hpp>

namespace tokyo
{

    class FontManager : NonCopyable
    {
    public:
        FontManager(const FileManager& _fileManager);
        bool loadFont(const std::string& _fontPath, const std::string& _fontName);
        sf::Font& getFont(const std::string& _fontName);
        const sf::Font& getFont(const std::string& _fontName) const;

    private:
        const FileManager& _fileManager;
        std::unordered_map<std::string, sf::Font*> m_Fonts;
    };
}