#pragma once
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>
#include <string>

#include "Defines.h"

namespace deq
{

	class TextureManager
	{
		std::unordered_map<std::string, sf::Texture> m_textures;

	public:
		
		sf::Texture* loadTexture(std::string path);

		// Singleton
		TextureManager() {}
		static TextureManager& getInstance();
		TextureManager(TextureManager const&) = delete;
		void operator=(TextureManager const&) = delete;
	};

	sf::Texture* loadTexture(std::string path);

}