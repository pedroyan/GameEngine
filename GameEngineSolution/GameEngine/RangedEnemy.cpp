#include "RangedEnemy.h"
#include "Camera.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Sound.h"
#include "Animation.h"
#include "Raio.h"
float attackDurationRanged = 1.5;


RangedEnemy::RangedEnemy(float x, float y) : Enemy(Sprite("img/RangedEnemyWalking.png", 7, 0.1,true), Sprite("img/RangedEnemyWalking.png", 7, 0.1),Sprite("img/rangedEnemyStairs.png")), attackingSprite("img/RangedEnemyAttack.png", 7, attackDurationRanged / 7), attackingSpriteVomito("img/RangedEnemyAttackVomito.png", 4, attackDurationRanged/5) {
	damage = 20;
	hp = 50;
	box.X = x;
	box.Y = y;
	box.W = actualSprite->GetWidth();
	box.H = actualSprite->GetHeight();
	attackRange = box.W*10;
	attackRangeVomito = box.W *5;
}


RangedEnemy::~RangedEnemy() {
}

void RangedEnemy::Update(float dt) {
	ApplyGravity(dt);
	if (focus != nullptr) {
		MoveToDumbly(focus->box.GetCenter());
		CheckAttack(dt);
		
		if (abs(focus->box.DistanceFrom(box)) <attackRangeVomito) {
			actualSprite = &attackingSpriteVomito;
		} else if(abs(focus->box.DistanceFrom(box)) <attackRange){
			actualSprite = &attackingSprite;
		}else {
			actualSprite = &walkingSprite;
		}
		if (focus->box.GetCenter().X - box.GetCenter().X <0) {
			walkingLeft = true;
		} else {
			walkingLeft = false;
		}
	}
	if (CurrentLayer == 1) {
		actualSprite = &stairsSprite;
	}
	actualSprite->Update(dt);
	auto result = MoveOnSpeed(dt);
	if (result & (int)CollisionFlags::Bottom) {
		Jump(3);
	}
}

void RangedEnemy::Render() {
	actualSprite->Render(box.GetWorldRenderPosition(), rotation, walkingLeft, Camera::Zoom);
}


void RangedEnemy::Attack() {
	
	Shoot();
	actualSprite = &attackingSprite;
	attackTimer.Update(-attackDurationRanged);
}

void RangedEnemy::Shoot() {
	auto position = box.GetCenter();
	auto angle = position.GetDistanceVectorAngle(this->focus->box.GetCenter());
	if (this->focus->box.DistanceFrom(box) <= attackRangeVomito) {
		auto bullet = new Bullet(position.X, position.Y, angle, 400, 1000, "img/rangedBulletVomito.png", 1, true, 30);
		Sound("audio/rangedAttackVomito.wav").Play(0);
		State& state = Game::GetInstance().GetCurrentState();
		state.AddObject(bullet);

	} else {
		auto  bullet = new Bullet(position.X, position.Y, angle, 600, 1500, "img/rangedBullet2.png", 6, true, 10);
		Sound("audio/rangedAttack.wav").Play(0);
		State& state = Game::GetInstance().GetCurrentState();
		state.AddObject(bullet);

		
	}

	
	
}

void RangedEnemy::CheckAttack(float dt) {
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
