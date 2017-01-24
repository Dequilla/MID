#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "Player.h"
#include "Textures.h"
#include "Collisions.h"

bool drawHitboxes = false;

int main(int argc, char** argv)
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1280, 720), "MID");

	sf::View view(sf::FloatRect(0.f, 0.f, 640.f, 360.f));
	window.setView(view);

	sf::Clock clock;
	sf::Time deltaTime;

	deq::Sprite sprite;
	sprite.setTexture(*deq::loadTexture("lights.png"));
	sprite.setPosition(200, 200);
	sprite.addFrame(sf::IntRect(96, 32, 32, 32));
	sprite.addFrame(sf::IntRect(128, 32, 32, 32));
	sprite.addFrame(sf::IntRect(160, 32, 32, 32));
	sprite.addAnimation("burn", std::vector<int>({ 1, 2, 3 }));
	sprite.addAnimation("none", std::vector<int>({ 1 }));
	sprite.setAnimation("burn");

	deq::AABB aabb;
	aabb.isStatic = true;
	aabb.left = 200;
	aabb.top = 200;
	aabb.width = 32;
	aabb.height = 32;
	deq::CollisionChecker::getInstance().addAABB(&aabb);

	deq::AABB aabb2;
	aabb2.isStatic = true;
	aabb2.left = 232;
	aabb2.top = 200;
	aabb2.width = 32;
	aabb2.height = 32;
	deq::CollisionChecker::getInstance().addAABB(&aabb2);

	deq::AABB aabb3;
	aabb3.isStatic = true;
	aabb3.left = 232;
	aabb3.top = 168;
	aabb3.width = 32;
	aabb3.height = 32;
	deq::CollisionChecker::getInstance().addAABB(&aabb3);

	deq::Player player;

	while (window.isOpen())
	{
		deltaTime = clock.restart();

		player.update(deltaTime.asSeconds());
		player.updateSprites(deltaTime.asSeconds());
		sprite.update(deltaTime.asSeconds());

		// Check collisions
		deq::CollisionChecker::getInstance().checkCollisions();

		sf::Event input;
		while (window.pollEvent(input))
		{
			player.checkInput(input);

			if (input.type == sf::Event::Closed)
				window.close();

			if (input.type == sf::Event::KeyPressed)
			{
				if (input.key.code == sf::Keyboard::RControl)
					drawHitboxes = !drawHitboxes;
			}
		}

		window.clear();

		window.draw(sprite);
		player.draw(window);

		if(drawHitboxes)
			deq::CollisionChecker::getInstance().drawDebug(window);

		window.display();
	}

	return 0;
}