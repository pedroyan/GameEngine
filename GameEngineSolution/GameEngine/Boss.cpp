#include "Boss.h"
#include "Camera.h"
#include "Bullet.h"
#include "TileCollision.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"
#include "Raio.h"

float attackDurationBoss = 1;
float attackDurationBossFire = 3;
float restDuration = 10;

Boss::Boss(float x, float y) : Enemy(Sprite("img/BossStairs.png",2,1), Sprite("img/BossWalking.png", 3, 0.1,true), Sprite("img/BossStairs.png", 2, 0.1)), attackingSprite("img/BossAttack.png", 3, attackDurationBoss / 3), attackingSpriteFire("img/BossAttackFire.png",5, attackDurationBoss/5),restSprite("img/BossRest.png",2,0.05){
	
	damage = 50;
	hp = 1000;
	box.X = x;
	box.Y = y;
	box.W = actualSprite->GetWidth();
	box.H = actualSprite->GetHeight();
	attackRange = box.W;
	attackRangeFire= box.W*10;
	CurrentLayer = 0;
}


Boss::~Boss() {
}

void Boss::Update(float dt) {
	ApplyGravity(dt);

	if (focus != nullptr) {
		if (CurrentLayer == 0) {
			
				Shoot();
			

				
					if (focus->box.GetCenter().GetDistance(box.GetCenter()) < 300) {
						MoveTo(Vec2(focus->box.X, focus->box.Y), dt);
					} else {
						DummyWalk(dt);
					}
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
		
		if (CurrentLayer == 1) {
			actualSprite = &stairsSprite;
		}
		if (stop) {
			actualSprite = &restSprite;

		}
		} else if (CurrentLayer == 1) {
			if (focus->box.Y > box.Y) {
				Speed.Y = +200;
			} else if (focus->box.Y < box.Y) {
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

void Boss::Render() {

	actualSprite->Render(box.GetWorldRenderPosition(), rotation, walkingLeft, Camera::Zoom);
}

void Boss::Shoot() {
	auto position = box.GetCenter();
	auto angle = position.GetDistanceVectorAngle(this->focus->box.GetCenter());
		auto  bullet = new Bullet(position.X, position.Y, angle, 400, 1000, "img/fire.png", 1, true, 0.1);
		Sound("audio/rangedAttack.wav").Play(0);
		State& state = Game::GetInstance().GetCurrentState();
		state.AddObject(bullet);
		attackTimerFire.Update(-attackDurationBossFire);

}

void Boss::Attack() {
	Sound("audio/MeleeEnemyAttack.wav").Play(0);
	focus->TakeDamage(50);
	
	attackTimer.Update(-attackDurationBoss);
}

void Boss::CheckAttack(float dt) {
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
