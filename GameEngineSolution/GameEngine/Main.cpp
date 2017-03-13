#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Logger.h"
#include "Vec2.h"

int main(int argc, char ** argv) {
	int Height = DEFAULT_GAME_HEIGHT;
	int Width = DEFAULT_GAME_WIDTH

	Game* game = new Game("Meu Jogo",Width,Height);
	game->Run();
	delete game;

	Vec2 vec = Vec2(10, 10);
	vec.Rotate(M_PI/4);
	float angle = vec.GetXAxisAngle();
	angle = angle * 180/ M_PI;

	return 0;
}