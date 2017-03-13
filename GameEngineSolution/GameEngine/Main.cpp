#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Logger.h"
#include "Vec2.h"
#include "Rect.h"
#include "Face.h"

int main(int argc, char ** argv) {
	int Height = DEFAULT_GAME_HEIGHT;
	int Width = DEFAULT_GAME_WIDTH

	Game* game = new Game("Meu Jogo",Width,Height);
	game->Run();
	delete game;

	return 0;
}