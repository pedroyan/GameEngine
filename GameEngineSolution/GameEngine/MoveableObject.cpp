#include "MoveableObject.h"
#include "TileCollision.h"
#include "Game.h"

MoveableObject::MoveableObject() {
}


MoveableObject::~MoveableObject() {
}

void MoveableObject::Move(float dt) {
	Rect previousRect = box;
	Rect stairsAnalisys = previousRect;
	stairsAnalisys.Y += Speed.Y*dt;
	stairsAnalisys.W = 0;
	stairsAnalisys.X += box.W / 2;

	if (CurrentLayer == 0) {//Tratamento de acoes caso o player esteja no layer 0 (fora das escadas)
		//EIXO Y
		auto collisionAnalysisLayer1 = TileCollision::isCollinding(stairsAnalisys, 1);
		if (collisionAnalysisLayer1 == TileCollision::Stairs && GoToStairs) {
			CurrentLayer = 1;
			CenterOnCurrentTile();
			return;
		}

		box.Y += Speed.Y*dt;//caso nao tenha colisao,aplicado a movimentacao normal em Y
		auto collisionAnalysisY = TileCollision::isCollinding(this->box, CurrentLayer);
		if (collisionAnalysisY == TileCollision::Solid) {
			Speed.Y = 0;
			box.Y = previousRect.Y;
		}

		//EIXO X
		box.X += Speed.X*dt;//caso nao tenha colisao,aplicado a movimentacao normal em X
		auto collisionAnalysisX = TileCollision::isCollinding(this->box, CurrentLayer);
		if (collisionAnalysisX == TileCollision::Solid) {
			box.X = previousRect.X;
		}
	}

	if (CurrentLayer == 1) {//Tratamento de acoes caso o player esteja no layer 1
		box.Y += Speed.Y*dt;
		auto collisionAnalysisLayer1 = TileCollision::isCollinding(this->box, 1);
		auto collisionAnalysisLayer0 = TileCollision::isCollinding(this->box, 0);
		if (QuitStairs && collisionAnalysisLayer0 != TileCollision::Solid) {
			CurrentLayer = 0;
			return;
		}

		if (collisionAnalysisLayer1 == TileCollision::noCollision && collisionAnalysisLayer0 != TileCollision::Solid) {
			CurrentLayer = 0;
			return;
		}
		if (collisionAnalysisLayer1 == TileCollision::Solid) {
			if (Speed.Y > 0) {
				CurrentLayer = 0;
			}
			box.Y = previousRect.Y;
			return;
		}

	}

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

