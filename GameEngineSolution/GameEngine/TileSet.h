#pragma once
#include <string>
#include "Sprite.h"

using std::string;
class TileSet {
	public:
		TileSet(int Width, int Height, string file);
		~TileSet();

		void Render(unsigned int index, float x, float y);

	private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
};

