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
		float SpeedLimit;

		int CurrentLayer = 0;

		bool inline OnStairs() { return CurrentLayer == 1; }
		static const float Gravity;

	protected:
		
		/// <summary>
		/// Movimenta o Moveable Object de acordo com a sua velocidade
		/// </summary>
		/// <param name="dt">Tempo, em segundos, decorrido entre a passagem de um frame e outro</param>
		/// <returns>Flags de colisão, indicando a direção onde ela ocorreu</returns>
		unsigned char MoveOnSpeed(float dt);

		/// <summary>
		/// Faz com que o moveable object pule
		/// </summary>
		/// <param name="height">Altura, em tiles, do pulo</param>
		void Jump(int height);

		/// <summary>
		/// Aplica a gravidade ao vetor velocidade do Moveable Object
		/// </summary>
		/// <param name="dt">Tempo, em segundos, decorrido entre a passagem de um frame e outro</param>
		void ApplyGravity(float dt);
	private:
		/// <summary>
		/// Centraliza o Moveable Object no tile em que ele se encontra
		/// </summary>
		void CenterOnCurrentTile();
};

