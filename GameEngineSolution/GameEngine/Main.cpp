#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Logger.h"

int main(int argc, char ** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	int Height = DEFAULT_GAME_HEIGHT;
	int Width = DEFAULT_GAME_WIDTH

	Game* game = new Game("Meu Jogo",Width,Height);

	SDL_Quit();

	return 0;
}