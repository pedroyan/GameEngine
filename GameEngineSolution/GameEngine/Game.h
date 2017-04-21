#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "State.h"
#include <stack>
#include <memory>

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

		void Push(State* state);

		void Run();
		float GetDeltaTime();

	private:
		static Game* Instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* storedState;
		int frameStart;
		float dt;
		std::stack<std::unique_ptr<State>> stateStack;
		void CalculateDeltaTime();
		void ManagePile();

};

