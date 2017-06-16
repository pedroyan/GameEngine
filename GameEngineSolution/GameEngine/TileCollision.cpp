#include "TileCollision.h"
#include "Game.h"
#include "InputManager.h"
#include <algorithm>

 TileMap TileCollision::map;
 int  TileCollision::tile_height;
 int TileCollision::tile_width;
 int TileCollision::map_height;
 int TileCollision::map_width;

 bool Order(int i, int j) { return (i<j); }

CollisionType TileCollision::PriorityCollision(Rect box,int layer) {
	
	auto collisions = GetCollisions(box, layer);
	std::sort(collisions.begin(), collisions.end());
	return collisions.back();
}

vector<CollisionType> TileCollision::GetCollisions(Rect box, int layer) {
	vector<CollisionType> toReturn;

	int left_tile = box.X / tile_width;
	int right_tile = (box.X + box.W) / tile_width;
	int top_tile = box.Y / tile_height;
	int bottom_tile = (box.Y + box.H) / tile_height;

	if (left_tile < 0) {
		left_tile = 0;
	}
	if (right_tile > map_width) {
		right_tile = map_width;
	}
	if (top_tile < 0) {
		top_tile = 0;
	}
	if (bottom_tile > map_height) {
		bottom_tile = tile_height;
	}

	CollisionType any_collision = CollisionType::noCollision;

	for (int i = left_tile; i <= right_tile; i++) {
		for (int j = top_tile; j <= bottom_tile; j++) {
			int* tile = map.At(i, j, layer);
			if (tile != nullptr) {
				toReturn.push_back(map.GetTileSet()->GetTileProperty(*tile));
			}
		}
	}
	return toReturn;
}

bool TileCollision::HasCollision(Rect box, int layer, CollisionType type) {
	auto collisions = GetCollisions(box, layer);
	for (auto& t : collisions) {
		if (t == type) {
			return true;
		}
	}
	return false;
}

void TileCollision::GetParameters(TileMap mapa){
	map = mapa;
	tile_height = map.GetTileSet()->GetTileHeight();
	tile_width = map.GetTileSet()->GetTileWidth();
	map_height = map.GetHeight();
	map_width = map.GetWidth();
}


