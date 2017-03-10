#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Logger.h"

int main(int argc, char ** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	// game code eventually goes here
	Game* game = new Game("Meu Jogo", 300, 300);

	SDL_Quit();

	return 0;
}