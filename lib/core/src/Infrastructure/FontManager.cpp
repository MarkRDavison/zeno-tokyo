#include <tokyo/Core/Infrastructure/FontManager.hpp>

namespace tokyo
{
	FontManager::FontManager(const FileManager& _fileManager) :
		_fileManager(_fileManager)
	{

	}
	bool FontManager::loadFont(const std::string& _fontPath, const std::string& _fontName)
	{
		sf::Font* font = new sf::Font();
		const auto& path = _fileManager.resolvePath(_fontPath);
		if (font->openFromFile(path))
		{
			m_Fonts[_fontName] = font;
			return true;
		}
		delete font;
		return false;
	}
	sf::Font& FontManager::getFont(const std::string& _fontName)
	{
		// TODO: Return default font
		return *(*m_Fonts.find(_fontName)).second;
	}
	const sf::Font& FontManager::getFont(const std::string& _fontName) const
	{
		// TODO: Return default font
		return *(*m_Fonts.find(_fontName)).second;
	}
}