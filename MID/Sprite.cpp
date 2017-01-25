#include "Sprite.h"

deq::Sprite::Sprite(std::string path)
{
	loadFromFile(path);
}

void deq::Sprite::loadFromFile(std::string path)
{
	std::unordered_map<std::string, int> frames;
	int totalFrames = 1;

	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		auto items = deq::split(line, ' ');
		std::string id = items.at(0);
		
		if (id.at(0) == '#')
			continue;

		if (id == "ss")
		{
			this->setTexture(*deq::loadTexture(items.at(1)));
		}
		else if (id == "fr")
		{
			frames.emplace(items.at(1), totalFrames);

			int posx = std::stoi(items.at(2));
			int posy = std::stoi(items.at(3));
			int width = std::stoi(items.at(4));
			int height = std::stoi(items.at(5));

			this->addFrame(sf::IntRect(posx, posy, width, height));

			totalFrames++;
		}
		else if (id == "an")
		{
			deq::Animation animation;

			std::string name = items.at(1);
			int frameCount = std::stoi(items.at(4));
			animation.frameTime = std::stoi(items.at(3));
			animation.loop = deq::stringToBool(items.at(2));
			for (int i = 1; i < frameCount + 1; i++)
			{
				animation.push_back(frames.at(items.at(i + 4)));
			}

			this->addAnimation(name, animation);
			this->setAnimation(name);
		}
		else
		{
			deq::assertMsg("Invalid id type while loading sprite...");
		}
	}

}

void deq::Sprite::update(float deltaTime)
{

	m_animationCounter += (float)m_animationSpeedUnit * deltaTime;

	if (!paused)
	{

		// If the frametime has reached it's end
		if (m_animationCounter >= m_currentAnimation.frameTime)
		{

			m_animationCounter = 0;
			
			if (m_currentFrame > m_currentAnimation.size() || m_currentFrame < 1)
			{
				if (!m_currentAnimation.loop)
					paused = true;
				else
					m_currentFrame = 1;
			}

			this->setFrame(m_currentAnimation.at(m_currentFrame - 1));
			m_currentFrame += 1;
		}

	}

}

void deq::Sprite::addAnimation(std::string id, deq::Animation animation)
{
	if (id.empty())
	{
		assertMsg("The id of animation being added was empty. Hint, animation id: " + id);

		return;
	}

	if (animation.size() < 1)
	{
		assertMsg("The animation being added had no frames. Hint, animation id: " + id);

		return;
	}

	m_animations.emplace(id, animation);
}

void deq::Sprite::setAnimation(std::string id)
{
	if (m_currentAnimationID == id)
		return;

	if (id.empty())
	{
		assertMsg("Animation id was empty when changing animation. Hint, animation id: " + id);

		return;
	}

	m_currentAnimationID = id;
	m_currentAnimation = m_animations.at(id);
	this->setFrame(m_currentAnimation.at(0));

	if (m_currentAnimation.size() == 1)
	{
		m_currentAnimation.loop = false;
		this->paused = true;
	}
	else
	{
		m_currentAnimation.loop = true;
		this->paused = false;
	}
}

void deq::Sprite::addFrames(std::vector<sf::IntRect> frames)
{
	for (auto frame : frames)
	{
		m_frames.emplace_back(frame);
	}
}

void deq::Sprite::addFrame(sf::IntRect frame)
{
	m_frames.push_back(frame);
}

void deq::Sprite::addFrame(int x, int y, int w, int h)
{
	m_frames.push_back(sf::IntRect(x, y, w, h));
}

void deq::Sprite::setFrame(int index)
{
	if (index > m_frames.size() || index < 1)
	{
		deq::assertMsg("Invalid frame index sent to sprite.");
	}

	this->setTextureRect(m_frames.at(index - 1));
}

deq::Animation::Animation(bool loop, int frameTime, int count, ...)
{
	this->loop = loop;
	this->frameTime = frameTime;

	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; ++i)
	{
		this->push_back(va_arg(args, int));
	}

	va_end(args);

}

void deq::Animation::addAnimation(int count, ...)
{
	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; ++i)
	{
		this->push_back(va_arg(args, int));
	}

	va_end(args);
}
