#pragma once
#include <string>
#include "Sprite.h"
#include "Vec2.h"
#include "Camera.h"
#include "GameObject.h"

using std::string;

class Bullet : public GameObject {
	public:
	Bullet(float x, float y, float angle, float speedArg, float maxDistance, string sprite, int frameCount, bool targetsPlayerv);
	~Bullet();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);

	bool targetsPlayer;

	private:

	Sprite sp;
	Vec2 speed;
	float distanceLeft;
};

