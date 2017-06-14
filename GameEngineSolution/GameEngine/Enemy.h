#pragma once
#include "GameObject.h"
#include "Player.h"
class Enemy : public GameObject {
	public:
		Enemy();
		virtual ~Enemy();
		void CreateDebugBox();
		bool inline IsEnemy() { return true; }
		bool inline IsDead() { return hp <= 0; }
		virtual void MoveTo(Vec2 pos);
		virtual void Focus(Player* focus);
		virtual void Attack() = 0;

	protected:
		Player* focus;
		int hp;

		/// <summary>
		/// Vers�o menos custosa do pathfinding, onde os inimigos s� se movimentam para a esquerda e direita, sem considerar escadas
		/// </summary>
		/// <param name="pos">posi��o de destino</param>
		void MoveToDumbly(Vec2 pos);
		
};

