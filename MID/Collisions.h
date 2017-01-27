#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

namespace deq
{

	class AABB : public sf::FloatRect 
	{
	public:
		AABB();
		AABB(sf::Vector2f position, sf::Vector2f size, bool isStatic = true);
		AABB(float left, float right, float width, float height, bool isStatic = true);

		bool isStatic = true;
	};

	typedef sf::Vector2f Point;

	// Singleton
	class CollisionChecker
	{
		std::vector<AABB*> m_staticColliders;
		std::vector<AABB*> m_dynamicColliders;

		std::vector<AABB*> m_copiedColliders;

	public:
		CollisionChecker() {}
		~CollisionChecker();

		void addAABB(AABB* aabb);
		void copyAABB(AABB aabb);

		void checkCollisions();

		void drawDebug(sf::RenderWindow& window);

		// Below: singleton stuff
		static CollisionChecker& getInstance();
		CollisionChecker(CollisionChecker const&) = delete;
		void operator=(CollisionChecker const&) = delete;

	};

	inline void drawAABB(sf::RenderWindow& window, const AABB& aabb, sf::Color color = sf::Color(255, 0, 0, 100));
	void addAABB(deq::AABB* aabb);
	void copyAABB(deq::AABB aabb);
}