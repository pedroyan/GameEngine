#pragma once
#include "GameObject.h"
enum class CollisionFlags:int {
	None = 0,
	Top = 1,
	Bottom = 2,
	Left = 4,
	Right = 8
};

class MoveableObject : public GameObject {
	public:
		MoveableObject();
		~MoveableObject();

		Vec2 Speed;
		bool GoToStairs;
		bool QuitStairs;

		int CurrentLayer = 0;

		bool inline OnStairs() { return CurrentLayer == 1; }
		static const float Gravity;

	protected:

		unsigned char Move(float dt);

		/// <summary>
		/// Faz com que o moveable object pule
		/// </summary>
		/// <param name="height">Altura em tiles do pulo</param>
		void Jump(int height);
	private:
		/// <summary>
		/// Centraliza o Moveable Object no tile em que ele se encontra
		/// </summary>
		void CenterOnCurrentTile();
};

