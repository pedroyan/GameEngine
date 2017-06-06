#include "Game.h"
#include "Debug.h"
void Debug::MakeDebugSquare(float x, float y, float w, float h, int r, int g, int b) {
		SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
		SDL_SetRenderDrawColor(renderer, r, g, b, 0);
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		SDL_RenderDrawRect(renderer, &rect);
	}

void Debug::MakeDebugSquare(float x, float y, float w, float h, SDL_Color color) {
	MakeDebugSquare(x, y, w, h, color.r, color.g, color.b);
}

void Debug::MakeCenteredDebugSquare(const Rect& positionBox, SDL_Color boxColor) {
	auto worldBox = positionBox.GetWorldBox();
	Debug::MakeDebugSquare(worldBox.X, worldBox.Y, worldBox.W, worldBox.H, boxColor);
	Debug::MakeDebugSquare(worldBox.X, worldBox.Y, worldBox.W, worldBox.H / 2, boxColor);
	Debug::MakeDebugSquare(worldBox.X, worldBox.Y, worldBox.W / 2, worldBox.H, boxColor);
}

Debug::Debug() {
}


