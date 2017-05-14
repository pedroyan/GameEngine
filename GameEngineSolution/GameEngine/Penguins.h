#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Timer.h"
#include "TileMap.h"

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
	TileMap map;


	float linearSpeed;
	float cannonAngle;
	int hp;
	Timer cooldownCounter;
	
	void Accelerate(bool forward, float dt);
	void UpdateCannonAngle(InputManager& manager);
	float getInertialBulletSpeed();
	void takeDamage(int damage);
	void applyTileEffect(float dt);

};

