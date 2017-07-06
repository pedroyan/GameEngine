#pragma once
#include "Sprite.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TileSet.h"
#include "State.h"
#include "TileMap.h"
#include "Music.h"
#include "Sound.h"
#include "Background.h"
#include "Timer.h"
#include "Portal.h"

class StageState : public State{
	public:
		StageState(string map, string tileSet, string music,string paralax = "img/ParalaxBlackCraftV1.png");
		~StageState();
		void LoadAssets();
		void Update(float dt);
		void Render();
		void Pause();
		void Resume();
		TileMap GetMap();
		void AddObject(GameObject* ptr);
		bool GetHordeMode();
		void EnableHordeMode();
		
	private:
		//variaveis
		Timer coolDownSpawnCounter;
		TileSet* tileSet;
		TileMap tileMap;
		Sprite bg;
		Music stageMusic;
		Background bg1;
		int playerLayer;

		//horde variables
		bool HordeMode;
		float cooldownSpawn;
		int enemyCount;
		std::vector<GameObject*> barrierArray;
		Timer zoomTimer;

		//metodos
		void CheckCollisions();
		void UpdateArray(float dt);
		void SpawnEnemy();
		void SpawnKeys();
};

