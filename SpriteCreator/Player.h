#pragma once

#include "Entity.h"
#include "Textures.h"
#include "Collisions.h"

namespace deq
{

	class Player : public Entity
	{
		bool m_moveUp = false;
		bool m_moveDown = false;
		bool m_moveLeft = false;
		bool m_moveRight = false;

		float m_speed = 50;

		deq::AABB m_aabb;

	public:

		Player();

		void update(float deltaTime);

		void moveX(float x);
		void moveY(float y);

		void checkInput(const sf::Event& input);
	};

}