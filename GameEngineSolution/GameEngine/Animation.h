#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Sprite.h"
#include <string>
using std::string;

class Animation : public GameObject {
	public:
	Animation(float x, float y, float rotation, Sprite sprite, float timeLimitV, bool ends);
	void Update(float dt);
	void Render();

	bool IsDead();

	void NotifyCollision(GameObject& other);
	bool Is(string type);
	~Animation();

	private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;
};

