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

class StageState : public State{
	public:
		StageState(string map, string tileSet,string paralax = "img/ParalaxBlackCraftV1.png", string music = "audio/CenarioDeGuerra.wav");
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
		bool HordeMode;
		float cooldownSpawn;

		//metodos
		void CheckCollisions();
		void UpdateArray(float dt);
		void SpawnEnemy();
		void SpawnKeys();
};

