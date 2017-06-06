#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Enemy : public GameObject {
	public:
		Enemy();
		Enemy(int x, int y);
		virtual ~Enemy();
		void CreateDebugBox();
		bool inline IsEnemy() { return true; }
		virtual void MoveTo(Vec2 pos);
		virtual void Focus(GameObject* focus);
		void Update(float dt);
		void Render();
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);

	private:
		GameObject* focus;
		Sprite sp;
		int hp, x, y;
};

