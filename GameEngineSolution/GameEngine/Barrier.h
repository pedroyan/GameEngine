#pragma once
#include "Rect.h"
#include "GameObject.h"
#include "Sprite.h"
class Barrier : public GameObject {
	public:
		/// <summary>
		/// Cria uma barreira de laser
		/// </summary>
		/// <param name="hp">hp da barreira</param>
		/// <param name="box">box da barreira</param>
		Barrier(int hp, Rect box);
		void Update(float dt);
		void Render();
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);

		~Barrier();
	private:
		int hp;
		int fullHealth;
		float frameDt;

		Sprite fullHp;
		Sprite midHp;
		Sprite lowHp;
		Sprite currentSp;

		void takeDamage(int dam);
};

