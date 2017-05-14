#include "TileCollision.h"
#include "Game.h"
TileCollision::CollisionType TileCollision::isCollinding(Rect box) {
	auto map = Game::GetInstance().GetCurrentState().GetMap();//talvez de como otimizar
	auto tile_height = map.GetTileSet()->GetTileHeight();
	auto tile_width = map.GetTileSet()->GetTileWidth();


	int left_tile =  box.X / tile_width;
	int right_tile = (box.X +  box.W) / tile_width;
	int top_tile =  box.Y / tile_height;
	int bottom_tile = (box.Y +  box.H) / tile_height;

	if (left_tile < 0) {
		left_tile = 0;
	}
	if (right_tile > tile_width) {
		right_tile = tile_width;
	}
	if (top_tile < 0) {
		top_tile = 0;
	}
	if (bottom_tile > tile_height) {
		bottom_tile = tile_height;
	}

	TileCollision::CollisionType	any_collision=noCollision;
	
	for (int i = left_tile; i <= right_tile; i++)
	{
		for (int j = top_tile; j <= bottom_tile; j++)
		{
			int* tile = map.At(i, j);
			if (map.GetTileSet()->GetTileProperty(*tile)==Solid) {
				if (any_collision < Solid) {
					any_collision = Solid;
				}
			}
			if (map.GetTileSet()->GetTileProperty(*tile) ==Snow ) {
				if (any_collision < Snow) {
					any_collision = Snow;
				}
			}
		}
	}
	return any_collision;
}
