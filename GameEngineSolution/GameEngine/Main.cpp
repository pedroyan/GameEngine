#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Logger.h"
#include "Vec2.h"
#include "Rect.h"
#include "Face.h"
#include "TileMap.h"

int main(int argc, char ** argv) {
	int Height = DEFAULT_GAME_HEIGHT;
	int Width = DEFAULT_GAME_WIDTH
	
	Game* game = new Game("PedroYan_140158995",Width,Height);
	game->Run();
	delete game;

	TileMap* map = new TileMap("map/tileMap.txt", nullptr);
	int* location = map->At(19, 23);
	(*location) = 30;
	int* location2 = map->At(19, 23);

	printf("oi");

	return 0;
}