#pragma once
#include <string>
#include "Sprite.h"
#include "Vec2.h"

using std::string;

class Bullet {
	public:
	Bullet(float x, float y, float angle, float speed, float maxDistance, string sprite);
	~Bullet();

	void Update(float dt);
	void Render();
	bool IsDead();

	private:

	Sprite sp;
	Vec2 speed;
	float distanceLeft;
};

