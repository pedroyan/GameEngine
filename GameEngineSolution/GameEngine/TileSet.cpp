#include "TileSet.h"
#include "Game.h"
#include "Debug.h"
#include "Camera.h"


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
	tileSet.Render(x, y,0,false,Camera::Zoom);
	#ifdef _DEBUG
		Debug::MakeDebugSquare(x*Camera::Zoom, y*Camera::Zoom, tileWidth*Camera::Zoom, tileHeight*Camera::Zoom, 0, 0, 255);
	#endif

	
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}

CollisionType TileSet::GetTileProperty(int tileIndex){
	auto iterator = tilesProperties.find(tileIndex);
	if (iterator == tilesProperties.end()) {
		return CollisionType::noCollision;
	} else {
		return iterator->second;
	}
}

void TileSet::AddTileProperty(int tileIndex, CollisionType tileType){
	auto map = tilesProperties.find(tileIndex);
	if (map == tilesProperties.end()) {
		this->tilesProperties.emplace(tileIndex,tileType);
		return;
	}
}
