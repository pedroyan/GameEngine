#include "MoveableObject.h"
#include "TileCollision.h"
#include "Game.h"
#include "Debug.h"

const float MoveableObject::Gravity = 2 * 9.8;

MoveableObject::MoveableObject() {
}


MoveableObject::~MoveableObject() {
}

unsigned char MoveableObject::MoveOnSpeed(float dt) {

	Rect previousRect = box;
	Rect stairsAnalisys = previousRect;

	//Monta uma linha da cintura do player pra baixo. Essa linha se estende
	//até 2 pixels abaixo do sprite (para detectar se há uma escada abaixo do player)
	stairsAnalisys.Y += +box.H/2;
	stairsAnalisys.H = box.H/2 + 2;
	stairsAnalisys.W = 0;
	stairsAnalisys.X += box.W / 2;

	unsigned char collisionFlags = (int)CollisionFlags::None;

	if (CurrentLayer == 0) {//Tratamento de acoes caso o player esteja no layer 0 (fora das escadas)
		//EIXO Y

		//Analisa a linha de colisão especial para escadas montada acima
		auto CollidingStairs = TileCollision::HasCollision(stairsAnalisys, 1, CollisionType::Stairs);
		if (CollidingStairs && GoToStairs) {
			CurrentLayer = 1;
			Speed.X = 0;
			CenterOnCurrentTile();
			return collisionFlags;
		}

		box.Y += Speed.Y*dt;//caso nao tenha colisao, aplicado a movimentacao normal em Y
		auto collisionAnalysisY = TileCollision::PriorityCollision(this->box, CurrentLayer);
		if (collisionAnalysisY == CollisionType::Solid) {
			if (box.Y > previousRect.Y) {
				collisionFlags = collisionFlags | (int)CollisionFlags::Bottom;
			} else {
				collisionFlags = collisionFlags | (int)CollisionFlags::Top;
			}
			Speed.Y = 0;
			box.Y = previousRect.Y; // caso acha colisão no eixo Y, o objeto permanece na sua antiga posição Y
		}

		//EIXO X
		box.X += Speed.X*dt;//caso nao tenha colisao,aplicado a movimentacao normal em X
		auto collisionAnalysisX = TileCollision::PriorityCollision(this->box, CurrentLayer);
		if (collisionAnalysisX == CollisionType::Solid) {
			if (box.X > previousRect.X) {
				collisionFlags = collisionFlags | (int)CollisionFlags::Right;
			} else {
				collisionFlags = collisionFlags | (int)CollisionFlags::Left;
			}
			box.X = previousRect.X;
		}
		return collisionFlags;
	}

	if (CurrentLayer == 1) {//Tratamento de acoes caso o objeto esteja na layer 1 (layer de escadas)
		box.Y += Speed.Y*dt;
		auto collisionAnalysisLayer1 = TileCollision::PriorityCollision(this->box, 1);
		auto collisionAnalysisLayer0 = TileCollision::PriorityCollision(this->box, 0);
		if (QuitStairs && collisionAnalysisLayer0 != CollisionType::Solid) {
			CurrentLayer = 0;
			return (int)CollisionFlags::None;
		}

		if (collisionAnalysisLayer1 == CollisionType::noCollision && collisionAnalysisLayer0 != CollisionType::Solid) {
			CurrentLayer = 0;
			return (int)CollisionFlags::None;
		}
		if (collisionAnalysisLayer1 == CollisionType::Solid) {
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
	auto k1 = 2 * Gravity * height;
	Speed.Y = -tileHeight *sqrt(k1);
}

void MoveableObject::ApplyGravity(float dt) {
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	Speed.Y += tileHeight * Gravity*dt;
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

