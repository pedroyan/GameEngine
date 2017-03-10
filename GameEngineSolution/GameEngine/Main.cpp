#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Logger.h"

int main(int argc, char ** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	IMG_Load("meuEgg.jpg");

	// game code eventually goes here

	SDL_Quit();

	return 0;
}