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
		/// <summary>
		/// Atualiza todos os sprites relacionados ao player,como subindo escada,corrida e etc
		/// </summary>
		/// <param name="dt">delta tempo dos trames</param>
		/// <param name="input">input dos botoes do teclado</param>
		void UpdateAllSprites(float dt, InputManager& input);
		void Shoot();
		void Bolt();

		static Player* playerInstance;

	private:
		Sprite bodySP;
		Sprite stairsSP;
		Sprite bodyRunSP;
		Sprite actualSP;
		Sprite jumpSP;
		Sprite armSP;
		Sprite playerLife;
		TileMap map;
		int keyCount;


		float linearSpeed;
		float cannonAngle;
		int fullHp;
		int hp;
		Timer cooldownCounter;
		Timer chargeCounter;
		int jumpCount; 
		bool movedLeft=false;

		void UpdateCannonAngle(InputManager& manager);
		float getInertialBulletSpeed();
		float getInertialBoltSpeed();
		void MovePlayer(float dt, InputManager& manager);
		void jumpPlayer();
		void UpdateConcertaArm(int correcaoX, int correcaoY, int correcaoLeft);
		int concertaX;
		int concertaY;
		int concertaLeft;

		void UpdateSpeedStairs(InputManager& input);
		void CenterOnCurrentTile();
};

