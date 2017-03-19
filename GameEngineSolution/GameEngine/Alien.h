#pragma once
#include "Vec2.h"
#include "Sprite.h"
#include <queue>
#include "GameObject.h"

using std::queue;

class Alien : public GameObject{
	public:
	Alien();
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
				Action(ActionType type, float x, float y);

				ActionType type;
				Vec2 pos;
		};


		Sprite sp;
		Vec2 speed;
		int hp;
		queue<Action> taskQueue;



};

