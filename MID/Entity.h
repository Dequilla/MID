#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "Sprite.h"

namespace deq
{

	class Entity
	{
	protected:
		std::vector<Sprite> m_sprites;

		float x = 0;
		float y = 0;

		float width = 16;
		float height = 16;

		bool m_animated = false;

	public:
		Entity() : x(0), y(0), width(16), height(16) {}
		Entity(float x, float y, float width, float height, bool animated = false);

		virtual void update(float deltaTime) = 0;

		void updateSprites(float deltaTime);

		virtual void draw(sf::RenderWindow& window);

		void addSprite(deq::Sprite& sprite);
		void copySprite(deq::Sprite sprite);
	};

}