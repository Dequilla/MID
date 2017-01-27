#include "Interface.h"

void deq::Interface::draw(sf::RenderWindow& window)
{
	for (auto &element : m_elements)
	{
		element->draw(window);
	}
}

void deq::Interface::input(const sf::Event& input)
{
	for (auto &element : m_elements)
	{
		element->input(input);
	}
}

void deq::Interface::update(const float& deltaTime)
{
	for (auto &element : m_elements)
	{
		element->update(deltaTime);
	}
}

void deq::Interface::addElement(std::string id, Element* element)
{
	m_elements.push_back(element);
	int index = m_elements.size() - 1;
	m_elementIndexs.emplace(id, index);
}

void deq::Interface::removeElement(std::string id)
{
	int index = m_elementIndexs.at(id);
	m_elements.erase(m_elements.begin() + index);
}

void deq::Interface::removeElement(int index)
{
	m_elements.erase(m_elements.begin() + index);
}

deq::Element* deq::Interface::getElement(std::string id)
{
	int index = m_elementIndexs.at(id);
	return m_elements.at(index);
}

deq::Element* deq::Interface::getElement(int index)
{
	return m_elements.at(index);
}

void deq::Button::updateDimensions()
{
	// Position
	sf::Vector2f leftPos = sf::Vector2f(m_position.x, m_position.y);
	sf::Vector2f centerPos = sf::Vector2f(m_position.x + m_sideSpriteWidth, m_position.y);
	sf::Vector2f rightPos = sf::Vector2f(centerPos.x + m_centerSpriteWidth, m_position.y);

	m_leftSprite.setPosition(leftPos);
	m_centerSprite.setPosition(centerPos);
	m_rightSprite.setPosition(rightPos);

	// Size
	m_sideSpriteWidth = m_size.x * 0.25f;
	m_centerSpriteWidth = m_size.x - m_sideSpriteWidth * 2;

	m_leftSprite.setSize(m_sideSpriteWidth, m_size.y);
	m_centerSprite.setSize(m_centerSpriteWidth, m_size.y);
	m_rightSprite.setSize(m_sideSpriteWidth, m_size.y);

	// Fit the text
	float size = m_size.y;
	size = size * 0.5f;
	m_text.setCharacterSize(size);

	if (m_text.getGlobalBounds().width > m_size.x)
	{
		// If text is too wide
		size = m_size.x / m_text.getString().getSize();
		size = size * 0.9f;
		m_text.setCharacterSize(size);
	}

	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
}

void deq::Button::updateButton(const float& deltaTime)
{
	// Update sprite looks
	if (pressed)
	{
		m_leftSprite.setAnimation("leftPressed");
		m_centerSprite.setAnimation("centerPressed");
		m_rightSprite.setAnimation("rightPressed");
	}
	else if (released)
	{
	}
	else
	{
		m_leftSprite.setAnimation("leftUnpressed");
		m_centerSprite.setAnimation("centerUnpressed");
		m_rightSprite.setAnimation("rightUnpressed");
	}

	m_leftSprite.update(deltaTime);
	m_centerSprite.update(deltaTime);
	m_rightSprite.update(deltaTime);

	released = false;
}

void deq::Button::init()
{
	m_leftSprite.setAnimation("leftUnpressed");
	m_centerSprite.setAnimation("centerUnpressed");
	m_rightSprite.setAnimation("rightUnpressed");
}

deq::Button::Button() : deq::Element(sf::Vector2f(0, 0), sf::Vector2f(100, 30))
{
	init();
	updateDimensions();
}

deq::Button::Button(sf::Vector2f position, sf::Vector2f size) : deq::Element(position, size)
{
	init();
	updateDimensions();
}

void deq::Button::draw(sf::RenderWindow& window)
{
	window.draw(m_leftSprite);
	window.draw(m_centerSprite);
	window.draw(m_rightSprite);

	window.draw(m_text);
}

void deq::Button::input(const sf::Event& input)
{
	if (input.type == sf::Event::MouseButtonPressed)
	{
		if (input.mouseButton.button == sf::Mouse::Button::Left)
		{
			sf::Vector2f mousePos(input.mouseButton.x, input.mouseButton.y);
			sf::FloatRect buttonBounds(this->m_position + globalInteractionOffset, this->m_size);
			if (buttonBounds.contains(mousePos))
			{
				pressed = true;
			}

		}
	}
	else if (input.type == sf::Event::MouseButtonReleased)
	{
		if (input.mouseButton.button == sf::Mouse::Left)
		{
			released = true;
			pressed = false;
		}
	}
}

void deq::Button::update(const float& deltaTime)
{
	updateButton(deltaTime);
}

void deq::Button::setFont(std::string path)
{
	m_font = loadFont(path);
	m_text.setFont(*m_font);

	updateDimensions();
}

void deq::Button::setText(sf::String text)
{
	m_text.setString(text);

	updateDimensions();
}

void deq::Button::setSize(float width, float height)
{
	m_size.x = width;
	m_size.y = height;

	updateDimensions();
}

void deq::Button::setPosition(float left, float top)
{	
	m_position.x = left;
	m_position.y = top;

	updateDimensions();
}

void deq::Button::setBackgroundColor(sf::Color color)
{
	m_centerSprite.setColor(color);
	m_leftSprite.setColor(color);
	m_rightSprite.setColor(color);
}

void deq::Button::setTextFillColor(sf::Color color)
{
	m_text.setFillColor(color);
}

deq::SelectFileButton::SelectFileButton() : deq::Button(sf::Vector2f(0, 0), sf::Vector2f(100, 30)){}

deq::SelectFileButton::SelectFileButton(sf::Vector2f position, sf::Vector2f size) : deq::Button(position, size){}

void deq::SelectFileButton::update(const float& deltaTime)
{

	if (released)
	{
		File file = openFileDialog("Open a spritesheet", "Images\0*.png;\0Any files\0*.*;\0\0"); // TODO: Change so it is not just a spritesheet button
	}

	updateButton(deltaTime);
}