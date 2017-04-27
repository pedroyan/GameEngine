#include "Sprite.h"
#include "Game.h"
#include "Logger.h"
#include "Resources.h"

Sprite::Sprite() {
	texture = nullptr;
	scaleX = 1;
	scaleY = 1;
}

Sprite::Sprite(string file) {
	texture = nullptr;
	scaleX = 1;
	scaleY = 1;
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

void Sprite::Render(int x, int y, float angle) {
	float degreeAngle = angle * 180 / M_PI;

	SDL_Renderer* renderer = Game::GetInstance()->GetRenderer();
	SDL_Rect destinyRectangl;

	destinyRectangl.x = x;
	destinyRectangl.y = y;
	destinyRectangl.h = clipRect.h*scaleY;
	destinyRectangl.w = clipRect.w*scaleY;
	SDL_RenderCopyEx(renderer, texture, &clipRect, &destinyRectangl,degreeAngle,nullptr,SDL_FLIP_NONE);
}

int Sprite::GetWidth() {
	return (int)width*scaleX;
}

int Sprite::GetHeight() {
	return (int)height*scaleY;
}

bool Sprite::IsOpen() {
	return texture != nullptr;
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;
}

void Sprite::SetScaleY(float scale) {
	scaleY = scale;
}


