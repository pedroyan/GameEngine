#pragma once
#include "GameObject.h"
class Enemy : public GameObject {
	public:
		Enemy();
		virtual ~Enemy();
		void CreateDebugBox();
		bool inline IsEnemy() { return true; }
		virtual void MoveTo(Vec2 pos);
		virtual void Focus(GameObject* focus);

	private:
		GameObject* focus;
};

