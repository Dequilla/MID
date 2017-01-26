#include "Entity.h"

deq::Entity::Entity(float x, float y, float width, float height, bool animated) : x(x), y(y), width(width), height(height), m_animated(animated)
{
}

void deq::Entity::updateSprites(float deltaTime)
{
	if (!m_animated)
		return;

	if (m_sprites.size() == 0)
		return;

	for (auto &sprite : m_sprites)
	{
		sprite.update(deltaTime);
	}

}

void deq::Entity::draw(sf::RenderWindow& window)
{

	if (m_sprites.size() == 0)
		return;

	for (auto &sprite : m_sprites)
	{
		window.draw(sprite);
	}

}

void deq::Entity::addSprite(deq::Sprite& sprite)
{
	m_sprites.push_back(sprite);
}

void deq::Entity::copySprite(deq::Sprite sprite)
{
	m_sprites.push_back(sprite);
}
