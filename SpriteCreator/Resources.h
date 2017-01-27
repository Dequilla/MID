#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

namespace deq
{

	class FontLoader
	{
		std::unordered_map<std::string, sf::Font> m_fonts;

	public:
		sf::Font* loadFont(std::string path);

		// Singleton
		FontLoader() {}
		static FontLoader& getInstance();
		FontLoader(FontLoader const&) = delete;
		void operator=(FontLoader const&) = delete;
	};

	sf::Font* loadFont(std::string path);
}