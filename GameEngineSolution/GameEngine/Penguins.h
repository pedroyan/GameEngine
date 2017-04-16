#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "InputManager.h"

class Penguins : public GameObject {
	public:
	Penguins(float x, float y);
	~Penguins();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);

	void Shoot();

	static Penguins* player;

	private:
	Sprite bodySP;
	Sprite cannonSp;
	Vec2 speed;

	float linearSpeed;
	float cannonAngle;
	int hp;
	
	void Accelerate(bool forward, float dt);
	void UpdateCannonAngle(InputManager& manager);
	float getInertialBulletSpeed();

};

