#include "TileSet.h"


TileSet::TileSet(int width, int height, string file) {
	tileSet = (*new Sprite(file));

	tileWidth = width;
	tileHeight = height;

	rows = tileSet.GetHeight() / height;
	columns = tileSet.GetWidth() / width;
}

TileSet::~TileSet() {
}

void TileSet::Render(unsigned int index, float x, float y) {
	unsigned int numberOfTiles = columns*rows;

	if (index >= numberOfTiles) {
		return;
	}

	int tileColumn = index%rows;
	int tileRow = index / rows;

	int positionX = tileColumn*tileWidth;
	int positionY = tileRow*tileHeight;

	tileSet.SetClip(positionX, positionY, tileWidth, tileHeight);
	tileSet.Render(x, y);
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}

