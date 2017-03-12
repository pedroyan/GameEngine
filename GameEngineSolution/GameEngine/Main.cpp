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

	Vec2 vec = Vec2(10, 8);
	Vec2 normalizedVec = vec.Normalize();
	float magnitude = normalizedVec.Magnitude();

	return 0;
}