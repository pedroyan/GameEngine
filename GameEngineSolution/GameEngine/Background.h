#pragma once
#include "Sprite.h"
#include "Game.h"
#include <string>

using std::string;

class Background {
	public:
		Background(string sprite, float velocity);
		void Render(int cameraX, int cameraY);
		Sprite bg;
		int width;
		int height;
		float velocity;
};