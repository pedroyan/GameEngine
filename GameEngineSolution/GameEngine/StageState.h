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
		StageState(string map, string tileSet);
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
		Music stageMusic;
		Background bg1;
		int playerLayer;

		//horde variables
		bool HordeMode;
		float cooldownSpawn;
		int enemyCount;
		std::vector<GameObject*> barrierArray;
		Timer zoomTimer;
		float zoomToValue;

		//metodos
		void CheckCollisions();
		void UpdateArray(float dt);
		void SpawnEnemy();
		void SpawnKeys();
};

