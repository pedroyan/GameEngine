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
		enum CollisionType {//quanto maior o enum,maior a prioridade da colissao
		noCollision=0,
		Floor,
		Wall
	}type;
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
	/// <summary>
	/// Analisa se o player esta colidindo com algo
	/// </summary>
	/// <returns>Tipo de colisao que o player esta sofrendo de maior prioridade</returns>
	CollisionType isCollinding();

};

