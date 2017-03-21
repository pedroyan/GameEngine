#pragma once
#include "Sprite.h"
#include <vector>
#include <memory>
#include "GameObject.h"

class State {
	public:
		State();
		~State();
		bool QuitRequested();
		void LoadAssets();
		void Update(float dt);
		void Render();
	private:
		//variaveis

		Sprite bg;
		std::vector<std::unique_ptr<GameObject>> objectArray;
		//metodos

		bool quitRequested;
		void Input();
		void AddObject(float mouseX, float mouseY);
};

