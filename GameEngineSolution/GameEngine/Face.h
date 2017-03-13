#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Face :
	public GameObject
{
	public:
		Face(float x, float y);
		~Face();

		void Damage(int damage);
		void Update(float dt);
		void Render();
		bool IsDead();
	private:
		int hitpoint;
		Sprite sp;
};

