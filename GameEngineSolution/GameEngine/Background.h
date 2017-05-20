#pragma once
#include "Sprite.h"
#include "Game.h"

class Background {
public:
	Background(char*, int, int, float);
	void Render(int, int);
	Sprite bg;
	int width;
	int height;
	float velocity;
};