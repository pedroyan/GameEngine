#pragma once
#include "GameObject.h"
class MoveableObject : public GameObject {
	public:
		MoveableObject();
		~MoveableObject();

		Vec2 Speed;
		bool CollisionY;
		bool CollisionX;
		bool GoToStairs;
		bool QuitStairs;

		int CurrentLayer = 0;

		bool inline OnStairs() { return CurrentLayer == 1; }

	protected:

		void Move(float dt);
	private:
		/// <summary>
		/// Centraliza o Moveable Object no tile em que ele se encontra
		/// </summary>
		void CenterOnCurrentTile();
};

