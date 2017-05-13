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

bool TileSet::isSolid(int tileSet) {
	auto iterator = tilesProperties.find(tileSet);
	if (iterator == tilesProperties.end()) {
		return false;
	} else {
		return iterator->second.GetIsSolid();
	}
}

bool TileSet::isSnow(int tileSet) {
	auto iterator = tilesProperties.find(tileSet);
	if (iterator == tilesProperties.end()) {
		return false;
	} else {
		return iterator->second.GetIsSnow();
	}
}

void TileSet::AddTileSnowProperty(int tileIndex, bool isSnow){
	auto map = tilesProperties.find(tileIndex);
	if (map == tilesProperties.end()) {
		auto tileIsSnow = TileProperties();
		tileIsSnow.SetIsSnow(isSnow);
		this->tilesProperties.emplace(tileIndex, tileIsSnow);
		return;
	}
	map->second.SetIsSnow(isSnow);
}

void TileSet::AddTileSolidProperty(int tileIndex, bool isSolid){
	auto map = tilesProperties.find(tileIndex);
	if (map == tilesProperties.end()) {
		auto tileIsSolid =  TileProperties();
		tileIsSolid.SetIsSolid(isSolid);
		this->tilesProperties.emplace(tileIndex,tileIsSolid);
		return;
	}
	map->second.SetIsSolid(isSolid);
}
