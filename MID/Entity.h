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

	public:

		virtual void update(float deltaTime) = 0;

		void updateSprites(float deltaTime);

		virtual void draw(sf::RenderWindow& window);

	};

}