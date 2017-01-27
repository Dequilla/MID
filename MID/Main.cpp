#include <SFML/Graphics.hpp>

#include "Map.h"
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
	//window.setVerticalSyncEnabled(true);

	sf::View view(sf::FloatRect(0.f, 0.f, 256.f, 144.f));
	sf::View fpsView(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));

	sf::Clock clock;
	sf::Time deltaTime;

	sf::Font font;
	font.loadFromFile("Assets/prstartk.ttf");
	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setString(sf::String(std::to_string(0) + " fps"));
	fpsText.setCharacterSize(34);
	fpsText.setPosition(10, 10);
	fpsText.setFillColor(sf::Color(255, 0, 0, 255));

	deq::Map map("Assets/Maps/map.map");

	while (window.isOpen())
	{
		deltaTime = clock.restart();

		map.updateMap(deltaTime.asSeconds());

		// Check collisions
		deq::CollisionChecker::getInstance().checkCollisions();

		sf::Event input;
		while (window.pollEvent(input))
		{
			map.checkInput(input);

			if (input.type == sf::Event::Closed)
				window.close();

			if (input.type == sf::Event::KeyPressed)
			{
				if (input.key.code == sf::Keyboard::RControl)
					showDebug = !showDebug;
			}
		}

		window.clear();

		window.setView(view);
		map.drawMap(window);

		if (showDebug)
		{
			deq::CollisionChecker::getInstance().drawDebug(window);

			window.setView(fpsView);
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