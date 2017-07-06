#include "MeleeEnemy.h"
#include "Camera.h"
#include "Bullet.h"
#include "TileCollision.h"
#include "Game.h"

float attackDuration = 1;

MeleeEnemy::MeleeEnemy(float x, float y) : Enemy(Sprite("img/MeleeEnemy.png"), Sprite("img/MeleeEnemy.png",6,0.1)), attackingSprite("img/MeleeEnemy_atk.png",6,attackDuration/6){
	damage = 10;
	hp = 100;
	box.X = x;
	box.Y = y;
	box.W = actualSprite->GetWidth();
	box.H = actualSprite->GetHeight();
	attackRange = box.W;
	CurrentLayer = 0;
}


MeleeEnemy::~MeleeEnemy() {
}

void MeleeEnemy::Update(float dt) {
	ApplyGravity(dt);

	if (focus != nullptr) {
		if (CurrentLayer == 0) {
			if (focus->box.GetCenter().GetDistance(box.GetCenter()) < 300) {
				MoveTo(Vec2(focus->box.X, focus->box.Y), dt);
			}
			else {
				DummyWalk(dt);
			}
			CheckAttack(dt);
		}
		else if (CurrentLayer == 1) {
			if (focus->box.Y > box.Y) {
				Speed.Y = +200;
			}
			else if (focus->box.Y < box.Y) {
				Speed.Y = -200;
			}
		}
	}

	auto collisionResult = MoveOnSpeed(dt);
	actualSprite->Update(dt);

	if (collisionResult & (int)CollisionFlags::Bottom) {
		ground = true;
	}

	if (!OnStairs() && GoToStairs) {
		GoToStairs = false;
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
