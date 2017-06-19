#include "MeleeEnemy.h"
#include "Camera.h"
#include "Bullet.h"

float attackDuration = 1;

MeleeEnemy::MeleeEnemy(float x, float y) : Enemy(Sprite("img/MeleeEnemy.png"), Sprite("img/MeleeEnemy.png",6,0.1)), attackingSprite("img/MeleeEnemy_atk.png",6,attackDuration/6){
	damage = 10;
	hp = 100;
	box.X = x;
	box.Y = y;
	box.W = actualSprite->GetWidth();
	box.H = actualSprite->GetHeight();
	attackRange = box.W;
}


MeleeEnemy::~MeleeEnemy() {
}

void MeleeEnemy::Update(float dt) {
	ApplyGravity(dt);
	if (focus!= nullptr) {
		MoveToDumbly(focus->box.GetCenter());
		CheckAttack(dt);
	}
	actualSprite->Update(dt);
	auto result = MoveOnSpeed(dt);
	if (result & (int)CollisionFlags::Bottom) {
		Jump(3);
	}
}

void MeleeEnemy::Render() {
	actualSprite->Render(box.GetWorldRenderPosition(), rotation, walkingLeft, Camera::Zoom);
}

void MeleeEnemy::NotifyCollision(GameObject & other) {
	if (other.Is("Bullet") && !static_cast<const Bullet&>(other).targetsPlayer) {
		hp -= other.damage;
	}
}

void MeleeEnemy::Attack() {
	focus->TakeDamage(10);
	actualSprite = &attackingSprite;
	attackTimer.Update(-attackDuration);
}

void MeleeEnemy::CheckAttack(float dt) {
	if (attackTimer.Get() != 0) {
		attackTimer.Update(dt);
		if (attackTimer.Get() > 0) {
			attackTimer.Restart();
			actualSprite = &stillSprite;
		}
	} else if (this->focus->box.DistanceFrom(box) <= attackRange) {
		Attack();
	}
}
