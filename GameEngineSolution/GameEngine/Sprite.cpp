#include "Sprite.h"
#include "Game.h"
#include "Logger.h"
#include "Resources.h"

Sprite::Sprite() {
	texture = nullptr;
	scaleX = 1;
	scaleY = 1;
}

Sprite::Sprite(string file, int VframeCount, float VframeTime) {
	texture = nullptr;
	scaleX = 1;
	scaleY = 1;

	frameCount = VframeCount;
	frameTime = VframeTime;

	Open(file);

	currentFrame = 0;
	timeElapsed = 0;

}


Sprite::~Sprite() {
}

void Sprite::Open(string file) {
	
	texture = Resources::GetImage(file);

	SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	frameWidth = width / frameCount; //realiza o cálculo somente uma vez

	SetClip(0, 0, frameWidth, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y, float angle) {
	float degreeAngle = angle * 180 / M_PI;

	SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
	SDL_Rect destinyRectangl;

	destinyRectangl.x = x;
	destinyRectangl.y = y;
	destinyRectangl.h = clipRect.h*scaleY;
	destinyRectangl.w = clipRect.w*scaleY;
	SDL_RenderCopyEx(renderer, texture.get(), &clipRect, &destinyRectangl,degreeAngle,nullptr,SDL_FLIP_NONE);
}

void Sprite::Render(Vec2 pos, float angle) {
	Render(pos.X, pos.Y, angle);
}

int Sprite::GetWidth() {
	return frameWidth*scaleX;
}

int Sprite::GetHeight() {
	return height*scaleY;
}

bool Sprite::IsOpen() {
	return texture != nullptr;
}

void Sprite::Update(float dt) {
	timeElapsed += dt;

	if (timeElapsed > frameTime) {
		currentFrame++;
		SetFrame(currentFrame);
		timeElapsed = 0;
	}

}

void Sprite::SetFrame(int frame) {
	frame = frame < frameCount ? frame : 0;
	currentFrame = frame;

	clipRect.x = frameWidth*frame;
}

void Sprite::SetFrameCount(int vframeCount) {
	frameCount = vframeCount;
}

void Sprite::SetFrameTime(float vframeTime) {
	frameTime = vframeTime;
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;
}

void Sprite::SetScaleY(float scale) {
	scaleY = scale;
}


