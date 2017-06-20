#include "Enemy.h"
#include "Debug.h"
#include "PriorityQueue.h"
#include "TileCollision.h"
#include "Pathfinding.h"
#include "Game.h"

const float jumpHeight = 2;
const float Gravity = 2 * 9.8;
const float sqrK1 = sqrt(2 * Gravity * jumpHeight);

Enemy::~Enemy() {
}

void Enemy::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box, { 250, 0, 0 });
}

void Enemy::MoveTo(Vec2 pos, float dt) {
	PriorityQueue<Vec2, double> frontier;
	Vec2 newPos;
	
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	
	auto neig = FindNeighbors(SpeedLimit * dt, tileHeight * sqrK1 * dt, pos);
	
	if (!neig.empty()) {
		for (auto next : neig) {
			frontier.put(next, heuristic(pos, next));
		}
		
		while (!frontier.empty()) {
			newPos = frontier.get();
			Rect newPosBox = box;
			newPosBox.X = newPos.X;
			newPosBox.Y = newPos.Y;
			auto collisionAnalysis = TileCollision::PriorityCollision(newPosBox, 0);
			
			if (collisionAnalysis == CollisionType::Solid) {
				continue;
			}
			
			if (collisionAnalysis == CollisionType::noCollision) {
				if (box.Y > newPos.Y) { //quero pular
					if (ground == 1 && speed.Y == 0) { //posso pular?
						box.X = newPos.X;
						speed.X = SpeedLimit;
						speed.Y = -tileHeight * sqrK1;
						break;
						
					} else {
						continue;
					}
				}
				else {
					box.X = newPos.X;
					speed.X = SpeedLimit;
					break;
				}
			}
		}
	}

	if (box.X != newPos.X) {//não andei
		Rect newPosBox = box;
		newPosBox.X = box.X + SpeedLimit * dt;
		newPosBox.Y = box.Y + tileHeight * sqrK1;
		auto collisionAnalysisR = TileCollision::PriorityCollision(newPosBox, 0);
		
		newPosBox.X = box.X - SpeedLimit * dt;
		newPosBox.Y = box.Y + tileHeight * sqrK1;
		auto collisionAnalysisL = TileCollision::PriorityCollision(newPosBox, 0);
		if (collisionAnalysisL == CollisionType::noCollision || collisionAnalysisR == CollisionType::noCollision) {//se eu pular eu contorno
			if (ground == 1 && speed.Y == 0) { //posso pular?
				speed.Y = -tileHeight * sqrK1;
			}
		}
	}
	
	if (box.X == pos.X && box.Y != pos.Y) {
		if (speedStairs.Y == 0) {
			if (box.Y > pos.Y) {
				speedStairs.Y = -SpeedLimit / 2;
			}
			else {
				speedStairs.Y = -SpeedLimit / 2;
			}
		}

		Rect previousRect = box;
		Rect stairsAnalisys = previousRect;
		stairsAnalisys.Y += speedStairs.Y*dt;
		stairsAnalisys.W = 0;
		stairsAnalisys.X += box.W / 2;

		auto collisionAnalysisLayer1 = TileCollision::PriorityCollision(stairsAnalisys, 1);
		if (collisionAnalysisLayer1 == CollisionType::Stairs) {
		}
	}
}

void Enemy::Focus(Player* focus) {
	this->focus = focus;
}

Enemy::Enemy(Sprite stillSprite, Sprite walkingSprite) : stillSprite(stillSprite), walkingSprite(walkingSprite) {
	focus = nullptr;
	actualSprite = &this->stillSprite;
}

void Enemy::MoveToDumbly(Vec2 pos) {
	//pathfinding tosco e menos custoso
}

std::list<Vec2> Enemy::FindNeighbors(float tileWidth, float tileHeight, Vec2 pos) {
	list<Vec2> neighbors;
	if (pos.X > box.X) {
		neighbors.push_back(Vec2(box.X + tileWidth, box.Y));
		neighbors.push_back(Vec2(box.X + tileWidth, box.Y - tileHeight));
	} else if (pos.X < box.X) {
		neighbors.push_back(Vec2(box.X - tileWidth, box.Y));
		neighbors.push_back(Vec2(box.X - tileWidth, box.Y - tileHeight));
	}
	
	return neighbors;
}