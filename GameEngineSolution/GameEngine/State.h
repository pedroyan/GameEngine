#pragma once
#include "Sprite.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"

class State {
	public:
		State();
		~State();
		bool QuitRequested();
		void Update(float dt);
		void Render();
	private:
		//variaveis

		Sprite bg;
		TileSet tileSet;
		TileMap tileMap;

		std::vector<std::unique_ptr<GameObject>> objectArray;
		//metodos

		bool quitRequested;
		void AddObject(float mouseX, float mouseY);
};

