#pragma once
#include <string>
#include <SDL_ttf.h>
#include <memory>
#include "Rect.h"
using std::string;
using std::shared_ptr;
class Text {
	public:
		enum TextStyle{SOLID,SHADED,BLENDED};
		Text(string fontFile,int fontsize, TextStyle style,
			 string text,SDL_Color color, int x = 0, int y =  0);
		~Text();
		
		void Render(int cameraX = 0, int cameraY = 0, float cameraZoom=1);
		void SetPos(int x, int y, bool centerX = false, bool centerY = false);
		void SetText(string text);
		void SetColor(SDL_Color color);
		void SetStyle(TextStyle style);
		void SetFontSize(int fontSize);

	private:
		void RemakeTexture();
		shared_ptr<TTF_Font> font;
		SDL_Texture* texture;

		string text;
		TextStyle style;
		int fontsize;
		SDL_Color color;
		Rect box;
};

