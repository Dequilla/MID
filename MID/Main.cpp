#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "Player.h"
#include "Textures.h"
#include "Collisions.h"

int main(int argc, char** argv)
{
	bool showDebug = false;
	float debugCounter = 0.f;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1280, 720), "MID");

	sf::View view(sf::FloatRect(0.f, 0.f, 640.f, 360.f));
	window.setView(view);
	//window.setVerticalSyncEnabled(true);

	sf::Clock clock;
	sf::Time deltaTime;

	sf::Font font;
	font.loadFromFile("Assets/prstartk.ttf");
	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setString(sf::String(std::to_string(0) + " fps"));
	fpsText.setCharacterSize(10);
	fpsText.setPosition(10, 10);
	fpsText.setFillColor(sf::Color(255, 0, 0, 255));

	deq::Sprite testSpr("Assets/Sprites/sprite.spr");
	testSpr.setScale(2.f, 2.f);

	deq::AABB aabb(200, 200, 32, 32, true);
	deq::addAABB(&aabb);

	deq::AABB aabb2(232, 200, 32, 32, true);
	deq::addAABB(&aabb2);

	deq::AABB aabb3(232, 168, 32, 32, true);
	deq::addAABB(&aabb3);

	deq::Player player;

	while (window.isOpen())
	{
		deltaTime = clock.restart();

		player.update(deltaTime.asSeconds());
		player.updateSprites(deltaTime.asSeconds());
		testSpr.update(deltaTime.asSeconds());

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
					showDebug = !showDebug;
			}
		}

		window.clear();

		window.draw(testSpr);
		player.draw(window);

		if (showDebug)
		{
			// Collision boxes
			deq::CollisionChecker::getInstance().drawDebug(window);

			// Fps counter (avrage)
			window.draw(fpsText);
			debugCounter += 1000.f * deltaTime.asSeconds();
			if (debugCounter >= 500.f) // Once per second
			{
				debugCounter = 0;
				int fps = 1 / deltaTime.asSeconds();
				fpsText.setString(std::to_string(fps) + " fps");
			}
		}

		window.display();
	}

	return 0;
}