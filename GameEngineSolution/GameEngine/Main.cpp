#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "StageState.h"
#include "TitleState.h"
#include "Resources.h"

int wmain(int argc, char ** argv) {
	int Height = DEFAULT_GAME_HEIGHT;
	int Width = DEFAULT_GAME_WIDTH;


	Game* game = new Game("PedroYan_140158995",Width,Height);
	game->Push(new TitleState());
	game->Run();
	Game::ClearResources();
	delete game;

	return 0;
}