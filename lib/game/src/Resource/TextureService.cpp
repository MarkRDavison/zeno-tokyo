#include <tokyo/Game/Resource/TextureService.hpp>
#include <filesystem>

namespace tokyo
{
	TextureService::~TextureService()
	{
		for (auto& t : textures)
		{
			delete t.second;
		}
	}

	bool TextureService::loadTexture(const std::string& name, const std::string& path)
	{
		if (!std::filesystem::exists(path))
		{
			return false;
		}

		auto t = new sf::Texture();

		if (!t->loadFromFile(path))
		{
			delete t;
			return false;
		}

		if (auto existing = textures.find(name); existing != textures.end())
		{
			delete (*existing).second;
		}

		textures[name] = t;

		return true;
	}

	sf::Texture* TextureService::getTexture(const std::string& name) const
	{
		if (auto iter = textures.find(name); iter != textures.end())
		{
			return (*iter).second;
		}

		return nullptr;
	}
}