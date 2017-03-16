#include "Sprite.h"
#include "Game.h"
#include "Logger.h"
#include "Resources.h"

Sprite::Sprite() {
	texture = nullptr;
}

Sprite::Sprite(string file) {
	texture = nullptr;
	Open(file);
}


Sprite::~Sprite() {
	//if (texture!=nullptr) {
	//	SDL_DestroyTexture(texture);
	//}
}

void Sprite::Open(string file) {
	
	texture = Resources::GetImage(file);

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

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

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

bool Sprite::IsOpen() {
	return texture != nullptr;
}


