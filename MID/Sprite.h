#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <unordered_map>

#include "Defines.h"

namespace deq
{

	class Sprite : public sf::Sprite
	{
		// The positions in the texture where the sprites frames are located
		std::vector<sf::IntRect> m_frames;
		int m_currentFrame = 1;

		// Animations use the defined frames
		std::unordered_map<std::string, std::vector<int>> m_animations;
		std::vector<int> m_currentAnimation;
		std::string m_currentAnimationID;

		float m_animationCounter = 0;
		float m_animationSpeedUnit = 1000; // This means milliseconds


	public:
		int frameTime = 100;
		bool paused = false;
		bool loop = true;

		void update(float deltaTime);

		void addAnimation(std::string id, std::vector<int> animation);
		void setAnimation(std::string id);

		void addFrames(std::vector<sf::IntRect> frames);
		void addFrame(sf::IntRect frame);
		void addFrame(int x, int y, int w, int h);

		void setFrame(int index);
	};

}