#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "StageState.h"

#define DEFAULT_GAME_WIDTH 1024;
#define DEFAULT_GAME_HEIGHT 600;


using std::string;

class Game {
	public:
		Game(string title, int width, int height);
		~Game();

		static Game& GetInstance();
		SDL_Renderer* GetRenderer();
		State& GetCurrentState();

		void Run();
		float GetDeltaTime();

	private:
		static Game* Instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* storedState;
		int frameStart;
		float dt;
		void CalculateDeltaTime();

};

