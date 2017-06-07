#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include <list>

class Enemy : public GameObject {
	public:
		Enemy();
		Enemy(int x, int y, string sprite);
		virtual ~Enemy();
		void CreateDebugBox();
		bool inline IsEnemy() { return true; }
		virtual void MoveTo(Vec2 pos, float dt);
		virtual void Focus(GameObject* focus);
		void Update(float dt);
		void Render();
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);
		std::list<Vec2> FindNeighbors(float tileWidth, float tileHeight, Vec2 pos);

	private:
		GameObject* focus;
		Sprite sp;
		int hp, x, y;
		Vec2 speed;
		Vec2 speedStairs;
		int ground;
};

