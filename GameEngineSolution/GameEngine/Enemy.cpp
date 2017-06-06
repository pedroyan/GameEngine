#include "Enemy.h"
#include "Debug.h"
#include "Pathfinding.h"

Enemy::Enemy() {
	focus = nullptr;
}

Enemy::Enemy(int x, int y) : sp("img/jolteon.png"){
	focus = nullptr;
	rotation = 0;
	hp = 10;

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

void Enemy::MoveTo(Vec2 pos) {
	auto newPos = NextMove(box.GetCenter(), pos);
	box.X = newPos.X;
	box.Y = newPos.Y;
}

void Enemy::Focus(GameObject * focus) {
	this->focus = focus;
}


void Enemy::Update(float dt) {
	if (focus != nullptr && (box.GetCenter() - focus->box.GetCenter()).Magnitude() > 50) {
		MoveTo(Vec2((int)focus->box.GetCenter().X, (int)focus->box.GetCenter().Y));
	}
}

void Enemy::Render() {
	sp.Render(box.GetWorldPosition(), 0);
}

bool Enemy::IsDead() {
	return hp <= 0;
}

void Enemy::NotifyCollision(GameObject& other) {

}

bool Enemy::Is(string type) {
	return type == "Enemy";
}