#include "Map.h"

void deq::Map::loadMap(std::string path)
{
}

void deq::Map::drawMap(sf::RenderWindow& window)
{

	// DRAW GROUND TILES TODO TODO

	// Entity layers
	for (auto &layer : m_entityLayers)
	{
		for (auto &entity : layer)
		{
			
			entity.draw(window);

		}
	}

}

void deq::Map::updateMap(float deltaTime)
{

	for (auto &layer : m_entityLayers)
	{
		for (auto &entity : layer)
		{
			entity.update(deltaTime);
			entity.updateSprites(deltaTime);
		}
	}

}
