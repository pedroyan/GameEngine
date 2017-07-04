#pragma once
#include "GameObject.h"
#include "Sprite.h"
class Raio : public GameObject {
	public:
	Raio(float x, float y, float angle, float speedArg, float maxDistance, string sprite, int frameCount, bool targetsPlayerv, int damage = 0);
	Raio(float x, float y, float angle, float speedArg, float maxDistance, Sprite& sprite, bool targetsPlayerv, int damage = 0);
	~Raio();

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
	void Init(float x, float y, float angle, float maxDistance, bool targetsPlayerv, int damage);
	

};
