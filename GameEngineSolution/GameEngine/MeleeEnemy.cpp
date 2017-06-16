#include "MeleeEnemy.h"
#include "Camera.h"

float attackRange = 13;
float attackDuration = 1;

MeleeEnemy::MeleeEnemy(float x, float y) : Enemy(Sprite("img/MeleeEnemy.png"), Sprite("img/MeleeEnemy.png",6,0.1)), attackingSprite("img/MeleeEnemy_atk.png",6,attackDuration/6){
	damage = 10;
	
	box.X = x;
	box.Y = y;
	box.W = actualSprite->GetWidth();
	box.H = actualSprite->GetHeight();
}


MeleeEnemy::~MeleeEnemy() {
}

void MeleeEnemy::Update(float dt) {
	MoveToDumbly(focus->box.GetCenter());

	if (attackTimer.Get() != 0) {
		attackTimer.Update(dt);
		if (attackTimer.Get() > 0) {
			attackTimer.Restart();
			actualSprite = &stillSprite;
		}
	} else if (this->focus->box.DistanceFrom(box) <= 13) {
		Attack();
	}
}

void MeleeEnemy::Render() {
	actualSprite->Render(box.GetWorldRenderPosition(), rotation, walkingLeft, Camera::Zoom);
}

void MeleeEnemy::NotifyCollision(GameObject & other) {
}

void MeleeEnemy::Attack() {
	focus->TakeDamage(10);
	actualSprite = &attackingSprite;
	attackTimer.Update(-attackDuration);
}
