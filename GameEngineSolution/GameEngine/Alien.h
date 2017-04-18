#pragma once
#include "Vec2.h"
#include "Sprite.h"
#include <queue>
#include <vector>
#include "GameObject.h"
#include "Minion.h"
#include "Timer.h"

using std::queue;
using std::vector;

class Alien : public GameObject{
	public:
	Alien(float x, float y, int nMinions);
	~Alien();

	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	static int alienCount;

	private:
		Sprite sp;
		Vec2 speed;
		int hp;
		vector<Minion> minionArray;
		static Vec2 defaultSpeed;
		enum Alienstate { MOVING, RESTING };
		Alienstate state;
		Timer restTimer;
		Vec2 destination;

		void populateMinionArray(int nMinions);
		bool move(float dt, Vec2 targetPosition);
		Minion* getClosestMinion(Vec2 pos);
		void takeDamage(int damage);
		void runAI(float dt);
};

