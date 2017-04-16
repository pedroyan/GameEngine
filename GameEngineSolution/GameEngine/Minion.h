#pragma once
#include "GameObject.h"
#include "Sprite.h"
class Minion : public GameObject{
	public:
		Minion(GameObject* minionCenter, float arcOffset = 0);
		~Minion();

		void Update(float dt);
		void Render();
		bool IsDead();
		void Shoot(Vec2 pos);
		void NotifyCollision(GameObject& other);
		bool Is(string type);
	private:
		GameObject* center;
		Sprite sp;
		float arc;
		static float angularSpeed;
};

