#include "Collisions.h"

void deq::CollisionChecker::addAABB(AABB* AABB)
{
	if (AABB->isStatic)
	{
		m_staticColliders.push_back(AABB);
	}
	else
	{
		m_dynamicColliders.push_back(AABB);
	}
}

void deq::CollisionChecker::checkCollisions()
{
	//TODO: Implement a broad sweep

	// Fine sweep
	sf::FloatRect intersection; // The rectangle that reperesent how much and where it intersects
	for (auto const staticCollider : m_staticColliders)
	{

		for (auto const dynamicCollider : m_dynamicColliders)
		{

			if (dynamicCollider->intersects(*staticCollider))
			{
				dynamicCollider->intersects(*staticCollider, intersection); // Get the intersection data

				// Move only the smallest one
				float heightMultiplier = 1;
				float widthMultiplier = 1;
				if (intersection.width > intersection.height)
					widthMultiplier = 0;
				else
					heightMultiplier = 0;

				// https://yal.cc/rectangle-circle-intersection-test/
				// Fix by getting closest point
				// How much we need to move to get out
				float actualX = widthMultiplier * intersection.width;
				float actualY = heightMultiplier * intersection.height;

				// Center point check, get direction
				Point staticCenter(staticCollider->left + staticCollider->width / 2, staticCollider->top + staticCollider->height / 2);
				Point dynamicCenter(dynamicCollider->left + dynamicCollider->width / 2, dynamicCollider->top + dynamicCollider->height / 2);

				// Dynamic collider is above
				if (dynamicCenter.y < staticCenter.y)
				{
					dynamicCollider->top -= actualY;
				}
				// Dynamic collider is below
				else if (dynamicCenter.y > staticCenter.y)
				{
					dynamicCollider->top += actualY;
				}

				// Dynamic collider is to the left
				if (dynamicCenter.x < staticCenter.x)
				{
					dynamicCollider->left -= actualX;
				}
				else if (dynamicCenter.x > staticCenter.x)
				{
					dynamicCollider->left += actualX;
				}
			}

		}

	}

}

void deq::CollisionChecker::drawDebug(sf::RenderWindow& window)
{

	for (auto &stic : m_staticColliders)
	{
		drawAABB(window, *stic);
	}

	for (auto &dyn : m_dynamicColliders)
	{
		drawAABB(window, *dyn, sf::Color(0, 255, 0, 100));
	}

}

deq::CollisionChecker& deq::CollisionChecker::getInstance()
{
	static CollisionChecker instance;
	return instance;
}

void deq::drawAABB(sf::RenderWindow& window, const AABB& aabb, sf::Color color)
{
	sf::VertexArray lines(sf::LinesStrip, 5);
	lines[0].position = sf::Vector2f(aabb.left, aabb.top); // North West
	lines[1].position = sf::Vector2f(aabb.left, aabb.top + aabb.height); // South West
	lines[2].position = sf::Vector2f(aabb.left + aabb.width, aabb.top + aabb.height); // South east
	lines[3].position = sf::Vector2f(aabb.left + aabb.width, aabb.top); // North east
	lines[4] = lines[0];

	for (int i = 0; i < lines.getVertexCount(); i++)
	{
		lines[i].color = color;
	}

	window.draw(lines);
}

void deq::addAABB(deq::AABB* aabb)
{
	CollisionChecker::getInstance().addAABB(aabb);
}

deq::AABB::AABB() : sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(32, 32))
{
}

deq::AABB::AABB(sf::Vector2f position, sf::Vector2f size, bool isStatic) : sf::FloatRect(position, size)
{
	this->isStatic = isStatic;
}

deq::AABB::AABB(float left, float right, float width, float height, bool isStatic) : sf::FloatRect(sf::Vector2f(left, right), sf::Vector2f(width, height))
{
	this->isStatic = isStatic;
}
