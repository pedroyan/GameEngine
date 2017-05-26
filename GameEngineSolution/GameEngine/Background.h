#pragma once
#include "Sprite.h"
#include "Game.h"
#include "Camera.h"


class Background {
public:
	Background(char* sprite, float velocity);
	void Render(int cameraX, int cameraY);
	Sprite bg;
	int width;
	int height;
	float velocity;
};