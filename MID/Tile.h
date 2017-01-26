#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace deq
{

	class Tile : public Entity
	{
		

	public:
		Tile() : Entity() {}
		Tile(std::string spritePath, float x, float y, float width, float height, bool animated = false);
		Tile(deq::Sprite sprite, float x, float y, float width, float height, bool animated = false);
		
		void update(float deltaTime) { return; }
	};

}