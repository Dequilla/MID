#include "Entity.h"

void deq::Entity::updateSprites(float deltaTime)
{

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
