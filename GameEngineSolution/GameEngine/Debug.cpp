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
	auto pos = positionBox.GetWorldPosition();
	Debug::MakeDebugSquare(pos.X, pos.Y, positionBox.W, positionBox.H, boxColor);
	Debug::MakeDebugSquare(pos.X, pos.Y, positionBox.W, positionBox.H / 2, boxColor);
	Debug::MakeDebugSquare(pos.X, pos.Y, positionBox.W / 2, positionBox.H, boxColor);
}

Debug::Debug() {
}


