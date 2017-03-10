#include "Sprite.h"
#include "Logger.h"

Sprite::Sprite() {
	texture = nullptr;
}

Sprite::Sprite(string file) {
	texture = nullptr;
	Open(file);
}


Sprite::~Sprite() {
}

void Sprite::Open(string file) {
	Game* gameInstance = Game::GetInstance();
	texture = IMG_LoadTexture(gameInstance->GetRenderer(), file.c_str());

	if (texture == nullptr) {
		string error = SDL_GetError();
		Logger::LogError(error);
		exit(0);
	}

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	//Os valores de x e y seriam 0?
	SetClip(0, 0, width, height);

}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y) {
	SDL_Renderer* renderer = Game::GetInstance()->GetRenderer();
	SDL_Rect destinyRectangl;

	destinyRectangl.x = x;
	destinyRectangl.y = y;
	destinyRectangl.h = clipRect.h;
	destinyRectangl.w = clipRect.w;

	SDL_RenderCopy(renderer, texture, &clipRect, &destinyRectangl);
}


