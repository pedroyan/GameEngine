#include "RangedEnemy.h"
#include "Camera.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Sound.h"
#include "Animation.h"

float attackDurationRanged = 1.5;

RangedEnemy::RangedEnemy(float x, float y) : Enemy(Sprite("img/RangedEnemy.png"), Sprite("img/RangedEnemyWalking.png", 6, 0.1), Sprite("img/RangedEnemy.png", 1, 0.1)), attackingSprite("img/RangedEnemyAttack.png", 2, attackDurationRanged / 6) {
	damage = 20;
	hp = 50;
	box.X = x;
	box.Y = y;
	box.W = actualSprite->GetWidth();
	box.H = actualSprite->GetHeight();
	attackRange = box.W*10;
}


RangedEnemy::~RangedEnemy() {
}

void RangedEnemy::Update(float dt) {
	ApplyGravity(dt);
	if (focus != nullptr) {
		MoveToDumbly(focus->box.GetCenter());
		CheckAttack(dt);
		
		if (abs(focus->box.DistanceFrom(box)) <attackRange) {
			actualSprite = &attackingSprite;
		} else {
			actualSprite = &walkingSprite;
		}
		if (focus->box.GetCenter().X - box.GetCenter().X <0) {
			walkingLeft = true;
		} else {
			walkingLeft = false;
		}
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

void RangedEnemy::NotifyCollision(GameObject & other) {
	if (other.Is("Bullet") && !static_cast<const Bullet&>(other).targetsPlayer) {
		hp -= other.damage;
		if (IsDead()) {
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.GetWorldRenderPosition(), rotation, "img/morteEnemy70.png", 5, 0.125, true, Camera::Zoom));
			Sound("audio/enemyDeath.wav").Play(0);
		}
	}
}

void RangedEnemy::Attack() {
	
	Shoot();
	actualSprite = &attackingSprite;
	attackTimer.Update(-attackDurationRanged);
}

void RangedEnemy::Shoot() {

	auto position = box.GetCenter();

	auto angle = position.GetDistanceVectorAngle(this->focus->box.GetCenter());
	auto bullet = new Bullet(position.X, position.Y, angle, 400, 1000, "img/rangedBullet.png", 1, true,10);
	Sound("audio/rangedAttack.wav").Play(0);
	State& state = Game::GetInstance().GetCurrentState();
	state.AddObject(bullet);
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
