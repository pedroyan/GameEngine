#pragma once
#include "Enemy.h"
class MeleeEnemy : public Enemy {
	public:
		MeleeEnemy();
		~MeleeEnemy();
		void Update(float dt);
		void Render();
		void NotifyCollision(GameObject& other);
		bool inline Is(string type) { return type == "MeleeEnemy"; }
		void Attack();
};

