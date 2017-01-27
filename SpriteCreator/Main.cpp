#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Sprite.h"
#include "Player.h"
#include "Textures.h"
#include "Resources.h"
#include "Interface.h"
#include "Collisions.h"

int main(int argc, char** argv)
{
	bool showDebug = false;
	float debugCounter = 0.f;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1280, 720), "MID", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);

	sf::View fpsView(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));

	// Left side
	sf::View spriteView(sf::FloatRect(0.f, 0.f, 960.f, 720.f));
	spriteView.setViewport(sf::FloatRect(0.f, 0.f, 0.75f, 1.f));

	// Right side
	sf::View menuView(sf::FloatRect(0.f, 0.f, 320.f, 720.f));
	menuView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 1.f));

	deq::Sprite panelBG("Assets/ProgramResources/panel.spr");
	panelBG.setColor(sf::Color(232, 170, 94, 255));

	deq::Interface panel;
	deq::SelectFileButton* fileBtn = new deq::SelectFileButton(sf::Vector2f(70, 25), sf::Vector2f(200, 50));
	fileBtn->setFont("Assets/prstartk.ttf");
	fileBtn->setText("Open Spritesheet");
	fileBtn->setBackgroundColor(sf::Color(232, 170, 94, 255));
	fileBtn->globalInteractionOffset = sf::Vector2f(960.f, 0.f);
	panel.addElement("spritesheetbutton", fileBtn);

	deq::Sprite currentSprite("Assets/Sprites/player.spr");

	// Center sprite
	currentSprite.setPosition(960.f / 2.f - currentSprite.getLocalBounds().width / 2.f, 720.f / 2.f - currentSprite.getLocalBounds().height / 2);

	sf::Clock clock;
	sf::Time deltaTime;

	sf::Text fpsText;
	fpsText.setFont(*deq::loadFont("Assets/prstartk.ttf"));
	fpsText.setString(sf::String(std::to_string(0) + " fps"));
	fpsText.setCharacterSize(34);
	fpsText.setPosition(10, 10);
	fpsText.setFillColor(sf::Color(255, 0, 0, 255));

	while (window.isOpen())
	{
		deltaTime = clock.restart();

		currentSprite.update(deltaTime.asSeconds());
		panel.update(deltaTime.asSeconds());

		sf::Event input;
		while (window.pollEvent(input))
		{
			panel.input(input);

			if (input.type == sf::Event::Closed)
				window.close();

			if (input.type == sf::Event::KeyPressed)
			{
				if (input.key.code == sf::Keyboard::RControl)
					showDebug = !showDebug;
			}

			if (input.type == sf::Event::MouseWheelMoved)
			{
				float zoomFactor = 0;
				int in = input.mouseWheel.delta;
				if (in > 0)
					zoomFactor = 0.80f;
				else if (in < 0)
					zoomFactor = 1.20f;
				spriteView.zoom(zoomFactor);
			}
		}

		window.clear();

		window.setView(spriteView);
		window.draw(currentSprite);

		window.setView(menuView);
		window.draw(panelBG);
		panel.draw(window);

		if (showDebug)
		{
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

	delete fileBtn;

	return 0;
}