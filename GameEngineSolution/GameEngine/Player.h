#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Timer.h"
#include "TileMap.h"
#include "MoveableObject.h"

class Player : public MoveableObject {
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
		void TakeDamage(int damage);
		void UpdateSP(Sprite newSprite);
		void Shoot();

		static Player* playerInstance;

	private:
		Sprite bodySP;
		Sprite bodyRunSP;
		Sprite actualSP;
		Sprite armSp;
		TileMap map;
		int keyCount;


		float linearSpeed;
		float cannonAngle;
		int hp;
		Timer cooldownCounter;
		Timer chargeCounter;
		int jumpCount; 
		bool movedLeft=false;

		void UpdateCannonAngle(InputManager& manager);
		float getInertialBulletSpeed();
		void MovePlayer(float dt, InputManager& manager);
		void jumpPlayer();
		void UpdateConcertaArm(int correcaoX, int correcaoY, int correcaoLeft);
		int concertaX;
		int concertaY;
		int concertaLeft;

		void UpdateSpeedStairs(InputManager& input);
		void CenterOnCurrentTile();
};

