#include "TileCollision.h"
#include "Game.h"
#include "InputManager.h"
#include "TileMap.h"

 TileMap TileCollision::map;
 int  TileCollision::tile_height;
 int TileCollision::tile_width;
 int TileCollision::map_height;
 int TileCollision::map_width;

CollisionType TileCollision::isColliding(Rect box,int layer) {
	

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

	CollisionType any_collision= CollisionType::noCollision;

	for (int i = left_tile; i <= right_tile; i++)
	{
		for (int j = top_tile; j <= bottom_tile; j++) {
			int* tile = map.At(i, j,layer);
			if (tile != nullptr) {
				auto prop = map.GetTileSet()->GetTileProperty(*tile);

				if (prop == CollisionType::Solid && any_collision < CollisionType::Solid) {
					any_collision = CollisionType::Solid;
				} else if (prop == CollisionType::Stairs && any_collision < CollisionType::Stairs) {
					any_collision = prop;
				}	
			}
		}
	}
	return any_collision;
}

CollisionType TileCollision::isColliding(Vec2 point, int layer) {
	Rect singleBox(point.X, point.Y, 1, 1);
	return isColliding(singleBox, layer);
}

void TileCollision::GetParameters(TileMap mapa){
	map = mapa;
	tile_height = map.GetTileSet()->GetTileHeight();
	tile_width = map.GetTileSet()->GetTileWidth();
	map_height = map.GetHeight();
	map_width = map.GetWidth();
}


