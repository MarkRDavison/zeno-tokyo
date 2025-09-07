#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <cassert>

namespace tokyo
{
	TextureManager::TextureManager(const FileManager& _fileManager) :
		_fileManager(_fileManager)
	{

	}

	bool TextureManager::loadTexture(const std::string& _texturePath, const std::string& _textureName)
	{
		const auto& path = _fileManager.resolvePath(_texturePath);
		sf::Texture* texture = new sf::Texture();
		if (texture->loadFromFile(path))
		{
			m_Textures[_textureName] = texture;
			return true;
		}
		delete texture;
		return false;
	}

	sf::Texture& TextureManager::getTexture(const std::string& _textureName)
	{
		return *(*m_Textures.find(_textureName)).second;
	}
	const sf::Texture& TextureManager::getTexture(const std::string& _textureName) const
	{
		return *(*m_Textures.find(_textureName)).second;
	}

	bool TextureManager::createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo)
	{
		const unsigned startingSize = 32;
		return createAtlas(_atlasName, _subtextureInfo, startingSize);
	}
	bool TextureManager::createAtlas(const std::string& _atlasName, const std::vector<std::pair<std::string, std::string>>& _subtextureInfo, unsigned _startingSize)
	{
		unsigned size = _startingSize;
		sf::Image atlas;
		std::vector<std::pair<sf::Image, std::string>> imageNames;

		for (const auto& info : _subtextureInfo)
		{
			auto& ip = imageNames.emplace_back();
			ip.second = info.first;
			if (!ip.first.loadFromFile(info.second))
			{
				return false;
			}
		}

		bool valid = false;
		while (size <= MaxAtlasSize)
		{
			atlas.resize({size, size}, sf::Color::Magenta);

			if (tryCreateAtlasImage(_atlasName, atlas, imageNames))
			{
				valid = true;
				break;
			}

			std::cerr << "Failed to create atlas '" << _atlasName << "' with dimensions " << size << "x" << size << std::endl;

			size *= 2;
		}

		if (!valid)
		{
			return false;
		}

		sf::Texture* texture = new sf::Texture();
		if (texture->loadFromImage(atlas))
		{
			m_Textures[_atlasName] = texture;
			return true;
		}

		m_TextureAtlasInfo.erase(m_TextureAtlasInfo.find(_atlasName));

		delete texture;

		return false;
	}

	sf::FloatRect TextureManager::getAtlasSubTextureRect(const std::string& _atlasName, const std::string& _subTextureName) const
	{
		const auto& atlasInfo = m_TextureAtlasInfo.at(_atlasName);
		return atlasInfo.at(_subTextureName);
	}

	bool TextureManager::tryCreateAtlasImage(const std::string& _atlasName, sf::Image& _atlas, const std::vector<std::pair<sf::Image, std::string>>& _imageNamePairs)
	{
		std::unordered_map<std::string, sf::FloatRect> atlasInfo;

		assert(_atlas.getSize().x == _atlas.getSize().y);
		const unsigned size = _atlas.getSize().x;

		unsigned spacing = 1;
		unsigned currentX = spacing;
		unsigned currentY = spacing;
		unsigned maximumY = 0;

		for (const auto& inp : _imageNamePairs)
		{
			const auto& image = inp.first;
			const sf::Vector2u s = image.getSize();

			if (currentX + s.x + spacing > size)
			{
				// We are too wide, need to go to the next row
				currentX = spacing;
				currentY = maximumY;
			}

			if (currentY + s.y + spacing > size)
			{
				// We are too high, run out of room
				return false;
			}

			for (unsigned iy = 0; iy < s.y; ++iy)
			{
				for (unsigned ix = 0; ix < s.x; ++ix)
				{
					_atlas.setPixel({ currentX + ix, currentY + iy }, image.getPixel({ ix, iy }));
				}
			}

			sf::FloatRect bounds = sf::FloatRect(
				{ 
					(static_cast<float>(currentX) + 0.5f) / static_cast<float>(size),
					1.0f - ((static_cast<float>(currentY) - 0.5f) / static_cast<float>(size)) - static_cast<float>(s.y) / static_cast<float>(size) 
				},
				{
					static_cast<float>(s.x - 1) / static_cast<float>(size),
					static_cast<float>(s.y - 1) / static_cast<float>(size)
				}
			);

			atlasInfo[inp.second] = bounds;

			maximumY = std::max(maximumY, currentY + s.y + spacing);
			currentX += s.x + spacing;
		}

		m_TextureAtlasInfo[_atlasName] = atlasInfo;

		return true;
	}
}
