#include "MeleeEnemy.h"
#include "Camera.h"
#include "Bullet.h"
#include "TileCollision.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"
#include "Raio.h"

float attackDuration = 1;

MeleeEnemy::MeleeEnemy(float x, float y) : Enemy(Sprite("img/MeleeEnemy.png"), Sprite("img/MeleeEnemyWalking.png",6,0.1), Sprite("img/MeleeEnemyStairs.png",2, 0.1)), attackingSprite("img/meleeEnemyAttack.png",2,attackDuration/6){
	int randomEnemy = rand() % 3;
	switch (randomEnemy) {
	case 0:
	{
		stillSprite=Sprite("img/MeleeEnemy2.png");
		stairsSprite = Sprite("img/MeleeEnemyStairs2.png", 10, 0.3);
		walkingSprite = Sprite("img/MeleeEnemyWalking2.png", 8, 0.1);
		attackingSprite = Sprite("img/MeleeEnemyAttack2.png", 12, 0.1);
		damage = 30;
		hp = 200;
		box.X = x;
		box.Y = y;
		box.W = actualSprite->GetWidth();
		box.H = actualSprite->GetHeight();
		attackRange = box.W;
		ground = 1;
		CurrentLayer = 0;
		return;
		break;
	}
	default:
		break;
	}


	
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
		
		  if (abs(focus->box.DistanceFrom(box)) < attackRange*1.2) {
		  	actualSprite = &attackingSprite;
		  } else {
		  	actualSprite = &walkingSprite;
		  }
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
  
	if (CurrentLayer == 1) {
		actualSprite = &stairsSprite;
	}
  
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


void MeleeEnemy::Attack() {
	Sound("audio/meleeEnemyAttack.wav").Play(0);
	focus->TakeDamage(10);
	//actualSprite = &attackingSprite;
	attackTimer.Update(-attackDuration);
}

void MeleeEnemy::CheckAttack(float dt) {
	if (attackTimer.Get() != 0) {
		attackTimer.Update(dt);
		if (attackTimer.Get() > 0) {
			attackTimer.Restart();
			//actualSprite = &stillSprite;
		}
	} else if (this->focus->box.DistanceFrom(box) <= attackRange) {
		Attack();
	}
}
