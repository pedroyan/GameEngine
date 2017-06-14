#pragma once
#include "GameObject.h"
class Enemy : public GameObject {
	public:
		Enemy();
		virtual ~Enemy();
		void CreateDebugBox();
		bool inline IsEnemy() { return true; }
		bool inline IsDead() { return hp <= 0; }
		virtual void MoveTo(Vec2 pos);
		virtual void Focus(GameObject* focus);
		virtual void Attack() = 0;

	protected:
		GameObject* focus;
		int hp;

		/// <summary>
		/// Versão menos custosa do pathfinding, onde os inimigos só se movimentam para a esquerda e direita, sem considerar escadas
		/// </summary>
		/// <param name="pos">posição de destino</param>
		void MoveToDumbly(Vec2 pos);
		
};

