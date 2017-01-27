#pragma once
#include <SFML/Graphics.hpp>

#include <Windows.h>

#include <unordered_map>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "Resources.h"
#include "Sprite.h"

namespace deq
{
	class Element
	{
	protected:
		sf::Vector2f m_size;
		sf::Vector2f m_position;

	public:
		Element() : m_size(sf::Vector2f(32, 32)), m_position(sf::Vector2f(0, 0)) {}
		Element(sf::Vector2f position, sf::Vector2f size) : m_position(position), m_size(size) {}

		// Used to properly get interaction in another viewport
		sf::Vector2f globalInteractionOffset = sf::Vector2f(0.f, 0.f);

		virtual void draw(sf::RenderWindow& window) = 0;
		virtual void input(const sf::Event& input) = 0;
		virtual void update(const float& deltaTime) = 0;
	};

	class Interface
	{
	protected:
		// Params:		   string ID,  int INDEX
		std::unordered_map<std::string, int> m_elementIndexs;
		std::vector<Element*> m_elements;

	public:


		void draw(sf::RenderWindow& window);
		void input(const sf::Event& input);
		void update(const float& deltaTime);

		void addElement(std::string id, Element* element);
		void removeElement(std::string id);
		void removeElement(int index);

		Element* getElement(std::string id);
		Element* getElement(int index);
	};
	
	class Button : public Element
	{
	protected:
		sf::Text m_text;
		sf::Font* m_font;

		float m_sideSpriteWidth = 0.f;
		float m_centerSpriteWidth = 0.f;

		bool m_dialogOpened = false;

		deq::Sprite m_leftSprite = deq::Sprite("Assets/ProgramResources/button.spr");
		deq::Sprite m_centerSprite = deq::Sprite("Assets/ProgramResources/button.spr");
		deq::Sprite m_rightSprite = deq::Sprite("Assets/ProgramResources/button.spr");

		void updateDimensions();
		void updateButton(const float& deltaTime);
		void init();

	public:
		Button();
		Button(sf::Vector2f position, sf::Vector2f size);

		//bool isClicked = false;
		bool pressed = false;
		bool released = false;
		
		virtual void draw(sf::RenderWindow& window);
		virtual void input(const sf::Event& input);
		virtual void update(const float& deltaTime);

		void setFont(std::string path);
		void setText(sf::String text);
		void setSize(float width, float height);
		void setPosition(float left, float top);
		void setBackgroundColor(sf::Color color);
		void setTextFillColor(sf::Color color);
	};

	class SelectFileButton : public Button
	{
	public:
		SelectFileButton();
		SelectFileButton(sf::Vector2f position, sf::Vector2f size);

		virtual void update(const float& deltaTime);
	};

}