#pragma once
#include <string>
#include "Sprite.h"
#include "Vec2.h"
#include "Camera.h"
#include "GameObject.h"

using std::string;

class Bullet : public GameObject {
	public:
	Bullet(float x, float y, float angle, float speedArg, float maxDistance, string sprite, int frameCount);
	~Bullet();

	void Update(float dt);
	void Render();
	bool IsDead();

	private:

	Sprite sp;
	Vec2 speed;
	float distanceLeft;
};

