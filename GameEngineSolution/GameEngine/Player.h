#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Timer.h"
#include "TileMap.h"

class Player : public GameObject {
	public:
		Player(float x, float y);
		~Player();

		void Update(float dt);
		void Render();
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);
		void CreateDebugBox();
		int GetKeyCount() const;

		void UpdateSP(Sprite newSprite);
		void Shoot();

		static Player* playerInstance;

	private:
		Sprite bodySP;
		Sprite bodyRunSP;
		Sprite actualSP;
		Sprite cannonSp;
		Vec2 speed;
		Vec2 speedStairs;
		TileMap map;
		int keyCount;


		float linearSpeed;
		float cannonAngle;
		int hp;
		Timer cooldownCounter;
		Timer chargeCounter;
		int jumpCount;
		int currentLayer = 0; 
		bool movedLeft=false;

		void UpdateCannonAngle(InputManager& manager);
		float getInertialBulletSpeed();
		void takeDamage(int damage);
		void Move(float dt);

		void UpdateSpeedStairs(InputManager& input);
		void CenterOnCurrentTile();
};

