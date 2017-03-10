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

		Game* GetInstance();
		State* GetState();
		SDL_Renderer* GetRenderer();
		void Run();

	private:
		static Game* Instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* state;
};

