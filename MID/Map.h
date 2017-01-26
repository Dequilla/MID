#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

#include "Entity.h"
#include "Tile.h"

namespace deq
{

	class Map
	{
		std::vector<Tile> m_groundLayer;

		std::vector<std::vector<Entity>> m_entityLayers;

	public:
		Map() {}
		Map(const std::string& path);

		void loadMap(const std::string& path);

		void drawMap(sf::RenderWindow& window);

		void updateMap(float deltaTime);
	};

}