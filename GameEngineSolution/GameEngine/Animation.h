#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Sprite.h"
#include <string>
using std::string;

class Animation : public GameObject {
	public:
	Animation(Vec2 center, float rotationv, string sprite, int framecount, float frameTime, bool ends);
	void Update(float dt);
	void Render();

	bool IsDead();

	void NotifyCollision(GameObject& other);
	bool Is(string type);
	~Animation();

	private:
	Timer endTimer;
	float timeLimit;
	float zoom;
	bool oneTimeOnly;
	Sprite sp;
};

