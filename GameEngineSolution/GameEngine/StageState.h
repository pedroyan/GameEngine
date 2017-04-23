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

class StageState : public State{
	public:
		StageState();
		~StageState();
		void LoadAssets();
		void Update(float dt);
		void Render();
		void Pause();
		void Resume();
		void AddObject(GameObject* ptr);
	private:
		//variaveis

		Sprite bg;
		TileSet tileSet;
		TileMap tileMap;
		Music stageMusic;

		//metodos
		void CheckCollisions();
		void UpdateArray(float dt);
};

