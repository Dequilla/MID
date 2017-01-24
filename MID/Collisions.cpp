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

				// The dynamic collidercorners
				Point northWest(dynamicCollider->left, dynamicCollider->top);
				Point northEast(dynamicCollider->left + dynamicCollider->width, dynamicCollider->top);
				Point southWest(dynamicCollider->left, dynamicCollider->top + dynamicCollider->height);
				Point southEast(dynamicCollider->left + dynamicCollider->width, dynamicCollider->top + dynamicCollider->height);
				
				Point north(dynamicCollider->left + dynamicCollider->width / 2, dynamicCollider->top);
				Point west(dynamicCollider->left, dynamicCollider->top + dynamicCollider->height / 2);
				Point south(dynamicCollider->left + dynamicCollider->width / 2, dynamicCollider->top + dynamicCollider->height);
				Point east(dynamicCollider->left + dynamicCollider->width, dynamicCollider->top + dynamicCollider->height / 2);

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

				if (staticCollider->contains(north))
				{
					dynamicCollider->top += actualY;
				}
				else if (staticCollider->contains(south))
				{
					dynamicCollider->top -= actualY;
				}
				else if (staticCollider->contains(west))
				{
					dynamicCollider->left += actualX;
				}
				else if (staticCollider->contains(east))
				{
					dynamicCollider->left -= actualX;
				}
				else if (staticCollider->contains(northWest))
				{
					dynamicCollider->left += actualX;
					dynamicCollider->top  += actualY;
				}
				else if (staticCollider->contains(northEast))
				{
					dynamicCollider->left -= actualX;
					dynamicCollider->top  += actualY;
				}
				else if (staticCollider->contains(southEast))
				{
					dynamicCollider->left -= actualX;
					dynamicCollider->top  -= actualY;
				}
				else if (staticCollider->contains(southWest))
				{
					dynamicCollider->left += actualX;
					dynamicCollider->top  -= actualY;
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

float deq::calcTwoPointDist(Point p1, Point p2)
{
	float distx = (p2.x - p1.x);
	float disty = (p2.y - p1.y);
	distx *= distx; // POW by 2
	disty *= disty; // POW by 2

	float temp = distx - disty;
	if (temp < 0)
		temp *= -1;

	float dist = sqrt(temp);

	return dist;
}
