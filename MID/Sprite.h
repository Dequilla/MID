#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <stdarg.h>
#include <unordered_map>

#include "Textures.h"
#include "Defines.h"

namespace deq
{

	struct Animation : public std::vector<int>
	{
	public:
		Animation() : std::vector<int>() {}
		Animation(bool loop, int frameTime, int count, ...);

		void addAnimation(int count, ...);

		int frameTime = 200;
		bool loop = false;
	};

	class Sprite : public sf::Sprite
	{
		// The positions in the texture where the sprites frames are located
		std::vector<sf::IntRect> m_frames;
		int m_currentFrame = 1;

		// Animations use the defined frames
		std::unordered_map<std::string, Animation> m_animations;
		Animation m_currentAnimation;
		std::string m_currentAnimationID;

		float m_animationCounter = 0;
		float m_animationSpeedUnit = 1000; // This is the frame time's unit

	public:
		//int frameTime = 100;
		bool paused = false;
		//bool loop = true;

		Sprite() : sf::Sprite() {}
		Sprite(std::string path);
		void loadFromFile(std::string path);

		void update(float deltaTime);

		void addAnimation(std::string id, deq::Animation animation);
		void setAnimation(std::string id);

		void addFrames(std::vector<sf::IntRect> frames);
		void addFrame(sf::IntRect frame);
		void addFrame(int x, int y, int w, int h);

		void setFrame(int index);
	};

}