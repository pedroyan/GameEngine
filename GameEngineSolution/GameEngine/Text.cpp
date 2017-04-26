#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include "Logger.h"

Text::Text(string fontFile, int fontsize, TextStyle style, string text, SDL_Color color, int x, int y) {
	texture = nullptr;
	font = Resources::GetFont(fontFile, fontsize);
	this->style = style;
	this->text = text;
	this->color = color;
	box.X = x;
	box.Y = y;

	RemakeTexture();

}

Text::~Text() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Text::Render(int cameraX, int cameraY) {
	if (texture != nullptr) {
		auto renderer = Game::GetInstance().GetRenderer();

		SDL_Rect destiny;
		destiny.h = box.H;
		destiny.w = box.W;
		destiny.x = box.X - cameraX;
		destiny.y = box.Y - cameraY;

		int result = SDL_RenderCopy(renderer, texture, NULL, &destiny);
	}
}

void Text::SetPos(int x, int y, bool centerX, bool centerY) {
	if (centerX || centerY) {
		box.SetCenter(x, y);
		box.X = centerX ? box.X : x;
		box.Y = centerY ? box.Y : y;
	} else {
		box.X = x;
		box.Y = y;
	}
}

void Text::SetText(string text) {
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontsize = fontsize;
	RemakeTexture();
}

void Text::RemakeTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	SDL_Surface* surface = nullptr;

	switch (style) {
		case Text::SOLID:
			surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case Text::SHADED:
			SDL_Color black;
			black.r = 0; black.g = 0; black.b = 0; black.a = 255;
			surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, black);
			break;
		case Text::BLENDED:
			surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;
	}

	if (surface == nullptr) {
		Logger::LogError(SDL_GetError());
		exit(0);
	}

	box.W = surface->w;
	box.H = surface->h;

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_FreeSurface(surface);
}
