#pragma once
#include "Vec2.h"
#include "Sprite.h"
#include <queue>
#include <vector>
#include "GameObject.h"
#include "Minion.h"

using std::queue;
using std::vector;

class Alien : public GameObject{
	public:
	Alien(float x, float y, int nMinions);
	~Alien();

	void Update(float dt);
	void Render();
	bool IsDead();

	private:
		class Action {
			public:
				enum class ActionType {
					MOVE,
					SHOOT
				};
				Action(ActionType actionType, float x, float y);

				ActionType type;
				Vec2 pos;
		};


		Sprite sp;
		Vec2 speed;
		int hp;
		queue<Action> taskQueue;
		vector<Minion> minionArray;
		static Vec2 defaultSpeed;

		void populateMinionArray(int nMinions);
		void move(float dt, Alien::Action action);
		Minion* getClosestMinion(Vec2 pos);
};

