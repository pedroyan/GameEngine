#pragma once
#include "Sprite.h"
#include "Game.h"
#include <string>

using std::string;

class Background {
	public:
		Background(string sprite, float velocity);
		Background(float velocity);
		void Open(string sprite);
		void Render(int cameraX, int cameraY);
		Sprite bg;
		int width;
		int height;
		float velocity;
};