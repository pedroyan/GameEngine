#pragma once
#include "Enemy.h"
#include "Sprite.h"
#include "Timer.h"

class Boss : public Enemy {
	public:
	Boss(float x, float y);
	~Boss();
	void Update(float dt);
	void Render();
	//void NotifyCollision(GameObject& other);
	bool inline Is(string type) { return type == "MeleeEnemy"; }
	void Attack();
	void Shoot();
	bool stop=false;

	private:
	Sprite attackingSprite;
	Sprite attackingSpriteFire;
	Sprite restSprite;
	int attackRange;
	int attackRangeFire;
	Timer attackTimer;
	Timer attackTimerFire;
	Timer RestTimer;
	void CheckAttack(float dt);
};

