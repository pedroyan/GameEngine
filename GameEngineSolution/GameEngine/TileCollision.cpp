#include "TileCollision.h"
#include "Game.h"
#include "InputManager.h"

 TileMap TileCollision::map;
 int  TileCollision::tile_height;
 int TileCollision::tile_width;
 int TileCollision::map_height;
 int TileCollision::map_width;

TileCollision::CollisionType TileCollision::isCollinding(Rect box,int layer) {
	

	int left_tile =  box.X / tile_width;
	int right_tile = (box.X +  box.W) / tile_width;
	int top_tile =  box.Y / tile_height;
	int bottom_tile = (box.Y +  box.H) / tile_height;

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

	TileCollision::CollisionType	any_collision=noCollision;

	for (int i = left_tile; i <= right_tile; i++)
	{
		for (int j = top_tile; j <= bottom_tile; j++) {
			int* tile = map.At(i, j,layer);
			if (tile != nullptr) {
				if (map.GetTileSet()->GetTileProperty(*tile) == Solid) {
					if (any_collision < Solid) {
						any_collision = Solid;
					}
				}
				else if (map.GetTileSet()->GetTileProperty(*tile) == Stairs) {
					if (any_collision < Stairs) {
						any_collision = Stairs;
					}
				}
			}
		}
	}
	return any_collision;
}

void TileCollision::GetParameters(TileMap mapa){
	map = mapa;
	tile_height = map.GetTileSet()->GetTileHeight();
	tile_width = map.GetTileSet()->GetTileWidth();
	map_height = map.GetHeight();
	map_width = map.GetWidth();
}


