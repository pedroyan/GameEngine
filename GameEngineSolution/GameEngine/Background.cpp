#include "Background.h"

Background::Background(char* sprite, float velocity) : bg(sprite) {
	this->width = bg.GetWidth();
	this->height = bg.GetHeight();
	this->velocity = velocity;
}

void Background::Render(int cameraX, int cameraY) {
	int actualX;
	int actualY;
	int widthGame = DEFAULT_GAME_WIDTH;
	int heightGame = DEFAULT_GAME_HEIGHT;

	if (cameraX <= 0) {
		actualX = 0;
	}
	else if(cameraX + widthGame >= width) {
		actualX = width - widthGame;
	}
	else {
		actualX = cameraX;
	}

	if (cameraY <= 0) {
		actualY = 0;
	}
	else if (cameraY + heightGame >= height) {
		actualY = height - heightGame;
	}
	else {
		actualY = cameraY;
	}

	bg.Render(-actualX*velocity, -actualY*velocity);
}