#include "Resources.h"

sf::Font* deq::FontLoader::loadFont(std::string path)
{
	if (m_fonts.count(path) < 1)
	{
		sf::Font font;
		font.loadFromFile(path);
		m_fonts.emplace(path, font);
	}

	return &m_fonts.at(path);
}

deq::FontLoader& deq::FontLoader::getInstance()
{
	static FontLoader instance;
	return instance;
}

sf::Font* deq::loadFont(std::string path)
{
	return FontLoader::getInstance().loadFont(path);
}
