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
	ground = 1;
}


MeleeEnemy::~MeleeEnemy() {
}

void MeleeEnemy::Update(float dt) {
	ApplyGravity(dt);

	if (focus != nullptr) {
		auto goindTo = Vec2(focus->box.X, focus->box.Y + (focus->box.H - box.H));

		if (goindTo.X - box.X > SpeedLimit*dt) {
			MoveTo(focus->box.GetCenter(), dt);
		} else {
			Rect newPosBox = box;
			newPosBox.X = goindTo.X;
			auto collisionAnalysisY = TileCollision::PriorityCollision(newPosBox, 0);
			if (collisionAnalysisY == CollisionType::noCollision) {
				box.X = goindTo.X;
			}
		}

		CheckAttack(dt);
	}

	actualSprite->Update(dt);
	//auto result = MoveOnSpeed(dt);
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	speed.Y += tileHeight * Gravity * dt;
	box.Y += speed.Y*dt;
	
	auto collisionAnalysisY = TileCollision::PriorityCollision(this->box, 0);
	if (collisionAnalysisY == CollisionType::Solid) {
		box.Y -= speed.Y*dt;
		ground = 1;
		speed.Y = 0;
	} else {
		ground = 0;
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
