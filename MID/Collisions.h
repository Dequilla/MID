#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

namespace deq
{

	class AABB : public sf::FloatRect 
	{
	public:
		bool isStatic = true;
	};

	typedef sf::Vector2f Point;

	// Singleton
	class CollisionChecker
	{
		std::vector<AABB*> m_staticColliders;
		std::vector<AABB*> m_dynamicColliders;

	public:
		CollisionChecker() {}

		void addAABB(AABB* AABB);

		void checkCollisions();

		void drawDebug(sf::RenderWindow& window);

		// Below: singleton stuff
		static CollisionChecker& getInstance();
		CollisionChecker(CollisionChecker const&) = delete;
		void operator=(CollisionChecker const&) = delete;

	};

	inline void drawAABB(sf::RenderWindow& window, const AABB& aabb, sf::Color color = sf::Color(255, 0, 0, 100));
	inline float calcTwoPointDist(Point p1, Point p2);

}