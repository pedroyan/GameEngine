#pragma once
#include "Enemy.h"
#include "Sprite.h"
#include "Timer.h"

class MeleeEnemy : public Enemy {
	public:
		MeleeEnemy(float x, float y);
		~MeleeEnemy();
		void Update(float dt);
		void Render();
		void NotifyCollision(GameObject& other);
		bool inline Is(string type) { return type == "MeleeEnemy"; }
		void Attack();

	private:
		Sprite attackingSprite;
		Timer attackTimer;
		void CheckAttack(float dt);
};

