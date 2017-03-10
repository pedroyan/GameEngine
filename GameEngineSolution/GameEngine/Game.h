#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "State.h"

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

