#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "StageState.h"
#include "TitleState.h"
#include "Resources.h"
#include "Pathfinding.h"

int wmain(int argc, char ** argv) {
	int a;
	//int Height = DEFAULT_GAME_HEIGHT;
	//int Width = DEFAULT_GAME_WIDTH;


	//Game* game = new Game("Jogo Final",Width,Height);
	//game->Push(new TitleState());
	//game->Run();
	//Game::ClearResources();
	//delete game;

	Pathfinding(Vec2(1, 4), Vec2(8, 5));

	scanf("%d", &a);
	return 0;
}