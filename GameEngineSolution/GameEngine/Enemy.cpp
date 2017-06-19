#include "Enemy.h"
#include "Debug.h"

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

Enemy::Enemy(Sprite stillSprite, Sprite walkingSprite) : stillSprite(stillSprite), walkingSprite(walkingSprite) {
	focus = nullptr;
	actualSprite = &this->stillSprite;
}

void Enemy::MoveToDumbly(Vec2 pos) {
	//pathfinding tosco e menos custoso
}
