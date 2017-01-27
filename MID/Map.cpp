#include "Map.h"

deq::Map::Map(const std::string& path)
{
	loadMap(path);
}

void deq::Map::loadMap(const std::string& path)
{
	std::unordered_map<std::string, deq::Sprite> spritesContainer;

	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line))
	{

		if (line.empty())
			continue;

		auto items = deq::split(line, ' ');
		std::string id = items.at(0);
		if (id.at(0) == '#')
			continue;

		if (id == "sp")
		{
			std::string name = items.at(1);
			Sprite sprite(items.at(2)); // Path

			spritesContainer.emplace(name, sprite);
		}
		else if (id == "gt") // Ground tile
		{

			std::string spriteName = items.at(1);
			float x = std::stof(items.at(2));
			float y = std::stof(items.at(3));
			float width = std::stof(items.at(4));
			float height = std::stof(items.at(5));

			if (spritesContainer.count(spriteName) < 1)
			{
				assertMsg("Failed to find defined sprite: " + spriteName + " in file: " + path);
				continue;
			}

			deq::Sprite sprite = spritesContainer.at(spriteName);
			sprite.setPosition(x, y);
			sprite.setSize(width, height);

			Tile tile;
			tile.copySprite(sprite);
			this->m_groundLayer.push_back(tile);
		}
		else if (id == "hb")
		{
			bool isStatic = stringToBool(items.at(1));
			float x = std::stof(items.at(2));
			float y = std::stof(items.at(3));
			float width = std::stof(items.at(4));
			float height = std::stof(items.at(5));

			AABB aabb(x, y, width, height, isStatic);
			copyAABB(aabb); // Copies aabb to the collision checker
		}
		else if (id == "en")
		{

		}
	}

}

void deq::Map::drawMap(sf::RenderWindow& window)
{

	for (auto &tile : m_groundLayer)
	{
		tile.draw(window);
	}

	// TEMP we really want player to be drawn at a z value inbetween entities
	player.draw(window);

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

	player.update(deltaTime);
	player.updateSprites(deltaTime);

	for (auto &layer : m_entityLayers)
	{
		for (auto &entity : layer)
		{
			entity.update(deltaTime);
			entity.updateSprites(deltaTime);
		}
	}

}

void deq::Map::checkInput(const sf::Event& input)
{
	player.checkInput(input);
}
