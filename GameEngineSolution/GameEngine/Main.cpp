#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Logger.h"
#include "Vec2.h"
#include "Rect.h"

int main(int argc, char ** argv) {
	int Height = DEFAULT_GAME_HEIGHT;
	int Width = DEFAULT_GAME_WIDTH

	Game* game = new Game("Meu Jogo",Width,Height);
	game->Run();
	delete game;

	/*Vec2 vec = Vec2(10, 10);
	vec.Rotate(M_PI/4);
	float angle = vec.GetXAxisAngle();
	angle = angle * 180/ M_PI;

	Rect testRect = Rect(0, 0, 10, 10);

	bool aval1 = testRect.IsInside(vec);
	bool aval2 = testRect.IsInside(Vec2(5, 5));
	bool aval3 = testRect.IsInside(Vec2(0, 0));
	bool aval4 = testRect.IsInside(Vec2(12, 0));*/

	return 0;
}