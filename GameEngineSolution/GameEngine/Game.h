#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "State.h"

#define DEFAULT_GAME_WIDTH 1024;
#define DEFAULT_GAME_HEIGHT 600;


using std::string;

class Game {
	public:
		Game(string title, int width, int height);

		~Game();

		static Game* GetInstance();
		State* GetState();
		SDL_Renderer* GetRenderer();
		void Run();
		float GetDeltaTime();

	private:
		static Game* Instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* state;
		int frameStart;
		float dt;
		void CalculateDeltaTime();

};

