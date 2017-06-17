#include "Enemy.h"
#include "Debug.h"
#include "Pathfinding.h"
#include "Game.h"

const float SpeedLimit = 200;

const float jumpHeight = 2;
const float Gravity = 2 * 9.8;
const float sqrK1 = sqrt(2 * Gravity * jumpHeight);

Enemy::Enemy() {
	focus = nullptr;
}

Enemy::Enemy(int x, int y, string sprite) : sp(sprite), speed(0,0){
	focus = nullptr;
	rotation = 0;
	hp = 10;
	ground = 1;

	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();
}

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
			auto collisionAnalysis = TileCollision::isCollinding(newPosBox, 0);

			if (collisionAnalysis == TileCollision::Solid) {
				continue;
			}

			if (collisionAnalysis == TileCollision::noCollision) {
				if (box.Y > newPos.Y) { //quero pular
					if (ground == 1 && speed.Y == 0) { //posso pular?
						box.X = newPos.X;
						speed.X = SpeedLimit;
						speed.Y = -tileHeight * sqrK1;
						break;
					}
					else {
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
		auto collisionAnalysisR = TileCollision::isCollinding(newPosBox, 0);

		newPosBox.X = box.X - SpeedLimit * dt;
		newPosBox.Y = box.Y + tileHeight * sqrK1;
		auto collisionAnalysisL = TileCollision::isCollinding(newPosBox, 0);
		if (collisionAnalysisL == TileCollision::noCollision || collisionAnalysisR == TileCollision::noCollision) {//se eu pular eu contorno
			if (ground == 1 && speed.Y == 0) { //posso pular?
				speed.Y = -tileHeight * sqrK1;
			}
		}
	}

	if (box.X == pos.X && box.Y != pos.Y) {
		if(speedStairs.Y == 0) {
			if (box.Y > pos.Y) {
				speedStairs.Y = -SpeedLimit / 2;
			} else {
				speedStairs.Y = -SpeedLimit / 2;
			}
		}
			
		Rect previousRect = box;
		Rect stairsAnalisys= previousRect;
			stairsAnalisys.Y += speedStairs.Y*dt;
			stairsAnalisys.W =0;
			stairsAnalisys.X += box.W/2;

		auto collisionAnalysisLayer1 = TileCollision::isCollinding(stairsAnalisys, 1);
		if (collisionAnalysisLayer1 == TileCollision::Stairs) {
		}
	}
}

void Enemy::Focus(GameObject * focus) {
	this->focus = focus;
}

void Enemy::Update(float dt) {
	if (focus != nullptr) {
		auto goindTo = Vec2(focus->box.X, focus->box.Y + (focus->box.H - box.H));
		if (goindTo.X - box.X > SpeedLimit*dt) {
			MoveTo(goindTo, dt);
		} else {
			Rect newPosBox = box;
			newPosBox.X = goindTo.X;
			auto collisionAnalysisY = TileCollision::isCollinding(newPosBox, 0);
			if (collisionAnalysisY == TileCollision::noCollision) {
				box.X = goindTo.X;
			}
		}
	}

	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	speed.Y += tileHeight * Gravity * dt;
	box.Y += speed.Y*dt;

	auto collisionAnalysisY = TileCollision::isCollinding(this->box, 0);
	if (collisionAnalysisY == TileCollision::Solid) {
		box.Y -= speed.Y*dt;
		ground = 1;
		speed.Y = 0;
	}
	else {
		ground = 0;
	}
}

void Enemy::Render() {
	sp.Render(box.GetWorldRenderPosition(), 0);
}

bool Enemy::IsDead() {
	return hp <= 0;
}

void Enemy::NotifyCollision(GameObject& other) {}

bool Enemy::Is(string type) {
	return type == "Enemy";
}

list<Vec2> Enemy::FindNeighbors(float tileWidth, float tileHeight, Vec2 pos) {
	list<Vec2> neighbors;
	if (pos.X > box.X) {
		neighbors.push_back(Vec2(box.X + tileWidth, box.Y));
		neighbors.push_back(Vec2(box.X + tileWidth, box.Y - tileHeight));
	} else if(pos.X < box.X) {
		neighbors.push_back(Vec2(box.X - tileWidth, box.Y));
		neighbors.push_back(Vec2(box.X - tileWidth, box.Y - tileHeight));
	}

	return neighbors;
}