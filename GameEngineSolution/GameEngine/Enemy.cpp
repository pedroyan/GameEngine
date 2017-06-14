#include "Enemy.h"
#include "Debug.h"


Enemy::Enemy() {
	focus = nullptr;
}


Enemy::~Enemy() {
}

void Enemy::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box, { 250, 0, 0 });
}

void Enemy::MoveTo(Vec2 pos) {
	//Pathfinding do carlos
}

void Enemy::Focus(Player* focus) {
	this->focus = focus;
}

void Enemy::MoveToDumbly(Vec2 pos) {
	//pathfinding tosco e menos custoso
}
