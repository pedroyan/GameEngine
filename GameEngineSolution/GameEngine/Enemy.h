#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Sprite.h"
#include "MoveableObject.h"
#include "Vec2.h"
#include <list>

class Enemy : public MoveableObject {
	public:
		void CreateDebugBox();
		bool inline IsEnemy() { return true; }
		bool inline IsDead() { return hp <= 0; }
		virtual void MoveTo(Vec2 pos, float dt);
		virtual void Focus(Player* focus);
		virtual void Attack() = 0;
		virtual void EnemyMove(float dt);
		virtual void DummyWalk(float dt);
		virtual ~Enemy();
		std::list<Vec2> FindNeighbors(float tileWidth, float tileHeight, Vec2 pos);

	protected:
		Player* focus;
		int hp, x, y;
		Vec2 speedStairs;
		bool ground;

		Sprite* actualSprite;
		Sprite stillSprite;
		Sprite walkingSprite;
		bool walkingLeft;
		int walked;

		Enemy(Sprite stillSprite, Sprite walkingSprite);

		/// <summary>
		/// Vers�o menos custosa do pathfinding, onde os inimigos s� se movimentam para a esquerda e direita, sem considerar escadas
		/// </summary>
		/// <param name="pos">posi��o de destino</param>
		void MoveToDumbly(Vec2 pos);
		
};

