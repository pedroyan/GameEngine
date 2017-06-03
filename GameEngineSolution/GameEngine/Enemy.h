#pragma once
#include "GameObject.h"
class Enemy : public GameObject {
	public:
		Enemy();
		virtual ~Enemy();

		//De Game Object
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
		virtual bool IsDead() = 0;
		virtual void NotifyCollision(GameObject& other) = 0;
		virtual bool Is(string type) = 0;

		void CreateDebugBox();
		bool inline IsEnemy() { return true; };

};

