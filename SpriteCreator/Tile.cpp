#include "Tile.h"

deq::Tile::Tile(std::string spritePath, float x, float y, float width, float height, bool animated) : Entity(x, y, width, height, animated)
{
	deq::Sprite sprite;
	sprite.loadFromFile(spritePath);
	this->copySprite(sprite);
}

deq::Tile::Tile(deq::Sprite sprite, float x, float y, float width, float height, bool animated) : Entity(x, y, width, height, animated)
{
	this->copySprite(sprite);
}
