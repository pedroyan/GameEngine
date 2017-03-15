#include "TileMap.h"


TileMap::~TileMap() {
}

TileMap::TileMap(string file, TileSet * tileSetVariable) {
	Load(file);
	tileSet = tileSetVariable;
}
