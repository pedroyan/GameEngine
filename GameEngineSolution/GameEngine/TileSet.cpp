#include "TileSet.h"
#include "Game.h"
#include "Debug.h"


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
	#ifdef _DEBUG
		Debug::MakeDebugSquare(x, y, tileWidth, tileHeight, 0, 0, 255);
	#endif

	
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}

TileSet::CollisionType TileSet::GetTileProperty(int tileIndex){
	auto iterator = tilesProperties.find(tileIndex);
	if (iterator == tilesProperties.end()) {
		return noCollision;
	} else {
		return iterator->second;
	}
}

void TileSet::AddTileProperty(int tileIndex, TileSet::CollisionType tileType){
	auto map = tilesProperties.find(tileIndex);
	if (map == tilesProperties.end()) {
		this->tilesProperties.emplace(tileIndex,tileType);
		return;
	}
}
