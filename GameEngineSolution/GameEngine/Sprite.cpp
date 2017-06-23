#include "Sprite.h"
#include "Game.h"
#include "Logger.h"
#include "Resources.h"
#include "Camera.h"

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

void Sprite::Render(int x, int y, float angle, bool flip, float zoom) {
	
	float degreeAngle = angle * 180 / M_PI;

	SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
	SDL_Rect destinyRectangl;

	destinyRectangl.x = ceil(x*zoom);
	destinyRectangl.y = ceil(y*zoom);
	destinyRectangl.h = ceil(clipRect.h*scaleY*zoom);
	destinyRectangl.w = ceil(clipRect.w*scaleX*zoom);
	if (flip) {
		SDL_RenderCopyEx(renderer, texture.get(), &clipRect, &destinyRectangl, degreeAngle, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopyEx(renderer, texture.get(), &clipRect, &destinyRectangl, degreeAngle, nullptr, SDL_FLIP_NONE);
	}
}

void Sprite::Render(Vec2 pos, float angle, bool flip, float zoom) {
	Render(pos.X, pos.Y, angle,flip,zoom);
}

int Sprite::GetWidth() {
	return (int)frameWidth*scaleX;
}

int Sprite::GetHeight() {
	return (int)height*scaleY;
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

Vec2 Sprite::GetCentralizedRenderPoint(Vec2 center) {
	Rect spRect(0, 0, clipRect.w, clipRect.h);
	spRect.SetCenter(center);
	return Vec2(spRect.X,spRect.Y);
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;
}

void Sprite::SetScaleY(float scale) {
	scaleY = scale;
}


