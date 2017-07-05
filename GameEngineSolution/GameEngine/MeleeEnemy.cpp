#include "MeleeEnemy.h"
#include "Camera.h"
#include "Bullet.h"
#include "TileCollision.h"
#include "Game.h"

float attackDuration = 1;

MeleeEnemy::MeleeEnemy(float x, float y) : Enemy(Sprite("img/MeleeEnemy.png"), Sprite("img/MeleeEnemyWalking.png",6,0.1), Sprite("img/MeleeEnemyStairs.png",2, 0.1)), attackingSprite("img/meleeEnemyAttack.png",2,attackDuration/6){
	damage = 10;
	hp = 100;
	box.X = x;
	box.Y = y;
	box.W = actualSprite->GetWidth();
	box.H = actualSprite->GetHeight();
	attackRange = box.W;
	ground = 1;
	CurrentLayer = 0;
}


MeleeEnemy::~MeleeEnemy() {
}

void MeleeEnemy::Update(float dt) {
	//ApplyGravity(dt);

	if (focus != nullptr) {
		MoveTo(focus->box.GetCenter(), dt);
		CheckAttack(dt);
	}
	if (CurrentLayer == 1) {
		actualSprite = &stairsSprite;
	}
	actualSprite->Update(dt);
	EnemyMove(dt);
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
