#include "Textures.h"

sf::Texture* deq::TextureManager::loadTexture(std::string path)
{
	if (m_textures.count(path) > 0)
		return &m_textures.at(path);

	sf::Texture temp;
	bool success = temp.loadFromFile(path);

	if (!success)
	{
		assertMsg("Texture " + path + " does not exists or has been moved, check your path");
		return nullptr;
	}

	m_textures.emplace(path, temp);

	return &m_textures.at(path);
}

deq::TextureManager& deq::TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}

sf::Texture* deq::loadTexture(std::string path)
{
	return TextureManager::getInstance().loadTexture(path);
}
