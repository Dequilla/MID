#include "Player.h"

deq::Player::Player()
{
	deq::Sprite sprite("Assets/Sprites/player.spr");

	m_aabb = deq::AABB(0, 0, 32, 32, false);
	deq::addAABB(&m_aabb);

	this->m_animated = true;

	this->m_sprites.emplace_back(sprite);
}

void deq::Player::update(float deltaTime)
{
	float velocity = m_speed * deltaTime;

	if (m_moveUp)
		moveY(-velocity);
	else if (m_moveDown)
		moveY(velocity);

	if (m_moveLeft)
	{
		moveX(-velocity);
		m_sprites.at(0).setAnimation("left");
	}
	else if (m_moveRight)
	{
		moveX(velocity);
		m_sprites.at(0).setAnimation("right");
	}
	else
		m_sprites.at(0).setAnimation("idle");


	this->x = m_aabb.left;
	this->y = m_aabb.top;
	this->m_sprites.at(0).setPosition(this->x, this->y);
}

void deq::Player::moveX(float x)
{
	this->m_aabb.left += x;
}

void deq::Player::moveY(float y)
{
	this->m_aabb.top += y;
}

void deq::Player::checkInput(const sf::Event& input)
{

	switch (input.type)
	{
	case sf::Event::KeyPressed:

		switch (input.key.code)
		{
		case sf::Keyboard::W:
			m_moveUp = true;
			break; // Keyboard W

		case sf::Keyboard::S:
			m_moveDown = true;
			break; // Keyboard S

		case sf::Keyboard::A:
			m_moveLeft = true;
			break; // Keyboard A

		case sf::Keyboard::D:
			m_moveRight = true;
			break; // Keyboard D

		default:
			break;
		} // Switch key code

		break; // KeyPressed

	case sf::Event::KeyReleased:

		switch (input.key.code)
		{
		case sf::Keyboard::W:
			m_moveUp = false;
			break; // Keyboard W

		case sf::Keyboard::S:
			m_moveDown = false;
			break; // Keyboard S

		case sf::Keyboard::A:
			m_moveLeft = false;
			break; // Keyboard A

		case sf::Keyboard::D:
			m_moveRight = false;
			break; // Keyboard D

		default:
			break;
		} // Switch key code

		break; // KeyReleased

	default:
		break;
	} // Switch event type

}
