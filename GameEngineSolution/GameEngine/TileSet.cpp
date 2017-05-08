#include "TileSet.h"


TileSet::TileSet(int width, int height, string file) : tileSet(file) {

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

	int tileColumn = index%columns;
	int tileRow = index / columns;

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

bool TileSet::isWall(int tileSet) {
	auto iterator = tilesProperties.find(tileSet);
	if (iterator == tilesProperties.end()) {
		return false;
	} else {
		return iterator->second.GetIsWall();
	}
	return true;
}

void TileSet::AddTilePropertie(int tileIndex, bool isWall){
	auto map = tilesProperties.find(tileIndex);
	if (map == tilesProperties.end()) {
		auto tileIsWall =  TileProperties();
		tileIsWall.SetIsWall(isWall);
		this->tilesProperties.emplace(tileIndex,tileIsWall);
		return;
	}
	map->second.SetIsWall(isWall);
}
