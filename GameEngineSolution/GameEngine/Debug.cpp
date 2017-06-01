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


