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
	CurrentLayer = 0;
}


MeleeEnemy::~MeleeEnemy() {
}

void MeleeEnemy::Update(float dt) {
	//ApplyGravity(dt);

	if (focus != nullptr) {
		auto goindTo = Vec2(focus->box.X, focus->box.Y + (focus->box.H - box.H));
		MoveTo(focus->box.GetCenter(), dt);
		CheckAttack(dt);
	}

	actualSprite->Update(dt);
	//auto result = MoveOnSpeed(dt);
	if (CurrentLayer == 0) {
		auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
		Speed.Y += tileHeight * Gravity * dt;
		box.Y += Speed.Y*dt;

		auto collisionAnalysisY = TileCollision::PriorityCollision(this->box, 0);
		if (collisionAnalysisY == CollisionType::Solid) {
			box.Y -= Speed.Y*dt;
			ground = 1;
			Speed.Y = 0;
		}
		else {
			ground = 0;
		}
	} else if (CurrentLayer == 1) {
		box.Y += Speed.Y*dt;
		auto collisionAnalysisLayer1 = TileCollision::PriorityCollision(this->box, 1);
		auto collisionAnalysisLayer0 = TileCollision::PriorityCollision(this->box, 0);

		if (collisionAnalysisLayer1 == CollisionType::noCollision && collisionAnalysisLayer0 != CollisionType::Solid) {
			CurrentLayer = 0;
			GoToStairs = false;
		}
		if (collisionAnalysisLayer1 == CollisionType::Solid) {
			if (Speed.Y > 0) {
				CurrentLayer = 0;
				GoToStairs = false;
			}
			box.Y -= Speed.Y*dt;
		}
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
