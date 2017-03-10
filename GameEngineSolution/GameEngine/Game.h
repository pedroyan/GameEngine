#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>

using std::string;

class Game {
	public:
		virtual ~Game();
		Game(string title, int width, int height);
		Game* GetInstance();
		//State* GetState();

	private:
		static Game* Instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		//State* state;
};

