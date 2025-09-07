#pragma once

#include <string>
#include <unordered_map>
#include <tokyo/Core/Infrastructure/FileManager.hpp>
#include <tokyo/Core/Utils/NonCopyable.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tokyo
{

    class TextureManager : NonCopyable
    {
    public:
        TextureManager(const FileManager& _fileManager);
        bool loadTexture(const std::string& _texturePath, const std::string& _textureName);

        sf::Texture& getTexture(const std::string& _textureName);
        const sf::Texture& getTexture(const std::string& _textureName) const;

        bool createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo);
        bool createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo, unsigned _startingSize);

        sf::FloatRect getAtlasSubTextureRect(const std::string& _atlasName, const std::string& _subTextureName) const;

    private:
        bool tryCreateAtlasImage(const std::string& _atlasName, sf::Image& _atlas, const std::vector<std::pair<sf::Image, std::string>>& _imageNamePairs);

        static constexpr const unsigned MaxAtlasSize{ 4096 };

    private:
        const FileManager& _fileManager;
        std::unordered_map<std::string, sf::Texture*> m_Textures;
        std::unordered_map<std::string, std::unordered_map<std::string, sf::FloatRect>> m_TextureAtlasInfo;
    };

}