#pragma once
#include "Enemy.h"
#include "Sprite.h"
#include "Timer.h"

class RangedEnemy : public Enemy {
	public:
	RangedEnemy(float x, float y);
	~RangedEnemy();
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool inline Is(string type) { return type == "RangedEnemy"; }
	void Attack();
	void Shoot();

	private:
	Sprite attackingSprite;
	int attackRange;
	Timer attackTimer;
	void CheckAttack(float dt);
};

