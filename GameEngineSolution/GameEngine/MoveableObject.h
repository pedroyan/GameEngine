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

		/// <summary>
		/// Velocidade do moveable object
		/// </summary>
		Vec2 Speed;

		/// <summary>
		/// Booleano indicando se o objeto quer ir para as escadas.
		/// Essa flag pode estar ativada mesmo sem nenhuma colisão com a escada
		/// </summary>
		bool GoToStairs;

		/// <summary>
		/// Booleano indicando se objeto quer sair das escadas
		/// Essa flag pode estar ativada mesmo sem nenhuma colisão com a escada
		/// </summary>
		bool QuitStairs;

		/// <summary>
		/// Limite do modulo da velocidade do moveable object
		/// </summary>
		float SpeedLimit;

		/// <summary>
		/// Layer em que o moveable object se encontra
		/// </summary>
		int CurrentLayer = 0;

		/// <summary>
		/// Indica se o moveable object está na layer de escadas
		/// </summary>
		/// <returns></returns>
		bool inline OnStairs() { return CurrentLayer == 1; }

		/// <summary>
		/// Constante de gravidade
		/// </summary>
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

		/// <summary>
		/// Centraliza o Moveable Object no tile em que ele se encontra
		/// </summary>
		void CenterOnCurrentTile();
};

