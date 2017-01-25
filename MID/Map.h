#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Entity.h"

namespace deq
{

	class Map
	{
		// TEMP TYPEDEF TODO
		typedef int Tile;
		std::vector<Tile> m_groundLayer;

		std::vector<std::vector<Entity>> m_entityLayers;

	public:
		void loadMap(std::string path);

		void drawMap(sf::RenderWindow& window);

		void updateMap(float deltaTime);
	};

}