#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace tokyo
{

	class TextureService
	{
	public:
		~TextureService();

		bool loadTexture(const std::string& name, const std::string& path);
		sf::Texture* getTexture(const std::string& name) const;

	private:
		std::unordered_map<std::string, sf::Texture*> textures;

	};

}