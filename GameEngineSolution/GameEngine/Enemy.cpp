#include "Enemy.h"
#include "Debug.h"


Enemy::Enemy() {
}


Enemy::~Enemy() {
}

void Enemy::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box, { 250, 0, 0 });
}
