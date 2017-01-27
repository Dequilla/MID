#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

#include "Collisions.h"
#include "Player.h"
#include "Entity.h"
#include "Tile.h"

namespace deq
{

	class Map
	{
		std::vector<Tile> m_groundLayer;

		std::vector<std::vector<Entity>> m_entityLayers;

		deq::Player player;

	public:
		Map() {}
		Map(const std::string& path);

		void loadMap(const std::string& path);

		void drawMap(sf::RenderWindow& window);

		void updateMap(float deltaTime);

		void checkInput(const sf::Event& input);
	};

}