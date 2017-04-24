#include "Text.h"
#include "Resources.h"
#include "Game.h"

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
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
}

void Text::SetFontSize(int fontSize) {
	this->fontsize = fontsize;
}

void Text::RemakeTexture() {
}
