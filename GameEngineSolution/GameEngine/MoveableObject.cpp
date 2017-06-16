#include "MoveableObject.h"
#include "TileCollision.h"
#include "Game.h"

const float MoveableObject::Gravity = 2 * 9.8;

MoveableObject::MoveableObject() {
}


MoveableObject::~MoveableObject() {
}

unsigned char MoveableObject::Move(float dt) {

	Rect previousRect = box;
	Rect stairsAnalisys = previousRect;
	stairsAnalisys.Y += Speed.Y*dt;
	stairsAnalisys.W = 0;
	stairsAnalisys.X += box.W / 2;
	unsigned char collisionFlags = (int)CollisionFlags::None;

	if (CurrentLayer == 0) {//Tratamento de acoes caso o player esteja no layer 0 (fora das escadas)
		//EIXO Y
		auto collisionAnalysisLayer1 = TileCollision::isCollinding(stairsAnalisys, 1);
		if (collisionAnalysisLayer1 == TileCollision::Stairs && GoToStairs) {
			CurrentLayer = 1;
			Speed.X = 0;
			CenterOnCurrentTile();
			return collisionFlags;
		}

		box.Y += Speed.Y*dt;//caso nao tenha colisao,aplicado a movimentacao normal em Y
		auto collisionAnalysisY = TileCollision::isCollinding(this->box, CurrentLayer);
		if (collisionAnalysisY == TileCollision::Solid) {
			if (box.Y > previousRect.Y) {
				collisionFlags = collisionFlags | (int)CollisionFlags::Bottom;
			} else {
				collisionFlags = collisionFlags | (int)CollisionFlags::Top;
			}
			Speed.Y = 0;
			box.Y = previousRect.Y;
		}

		//EIXO X
		box.X += Speed.X*dt;//caso nao tenha colisao,aplicado a movimentacao normal em X
		auto collisionAnalysisX = TileCollision::isCollinding(this->box, CurrentLayer);
		if (collisionAnalysisX == TileCollision::Solid) {
			if (box.X > previousRect.X) {
				collisionFlags = collisionFlags | (int)CollisionFlags::Right;
			} else {
				collisionFlags = collisionFlags | (int)CollisionFlags::Left;
			}
			box.X = previousRect.X;
		}
		return collisionFlags;
	}

	if (CurrentLayer == 1) {//Tratamento de acoes caso o player esteja no layer 1
		box.Y += Speed.Y*dt;
		auto collisionAnalysisLayer1 = TileCollision::isCollinding(this->box, 1);
		auto collisionAnalysisLayer0 = TileCollision::isCollinding(this->box, 0);
		if (QuitStairs && collisionAnalysisLayer0 != TileCollision::Solid) {
			CurrentLayer = 0;
			return (int)CollisionFlags::None;
		}

		if (collisionAnalysisLayer1 == TileCollision::noCollision && collisionAnalysisLayer0 != TileCollision::Solid) {
			CurrentLayer = 0;
			return (int)CollisionFlags::None;
		}
		if (collisionAnalysisLayer1 == TileCollision::Solid) {
			if (Speed.Y > 0) {
				CurrentLayer = 0;
			}
			box.Y = previousRect.Y;
			return (int)CollisionFlags::None;
		}

	}

}

void MoveableObject::Jump(int height) {
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	auto k1 = 2 * Gravity * Gravity;
	Speed.Y = -tileHeight *sqrt(k1);
}

void MoveableObject::CenterOnCurrentTile() {
	auto tileWidth = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileWidth();
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	auto center = box.GetCenter();
	int x = (int)center.X;

	int initialTileX = x - (x % tileWidth);
	int midTileX = initialTileX + (tileWidth / 2 - 1);

	box.SetCenter((float)midTileX, center.Y);
}

