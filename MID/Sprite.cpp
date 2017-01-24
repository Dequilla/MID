#include "Sprite.h"

void deq::Sprite::update(float deltaTime)
{

	m_animationCounter += (float)m_animationSpeedUnit * deltaTime;

	if (!paused)
	{

		// If the frametime has reached it's end
		if (m_animationCounter >= frameTime)
		{

			m_animationCounter = 0;
			
			if (m_currentFrame > m_currentAnimation.size() || m_currentFrame < 1)
			{
				if (!loop)
					paused = true;
				else
					m_currentFrame = 1;
			}

			this->setFrame(m_currentAnimation.at(m_currentFrame - 1));
			m_currentFrame += 1;
		}

	}

}

void deq::Sprite::addAnimation(std::string id, std::vector<int> animation)
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
		this->loop = false;
		this->paused = true;
	}
	else
	{
		this->loop = true;
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
