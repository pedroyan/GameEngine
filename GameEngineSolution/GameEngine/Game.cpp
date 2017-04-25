#include "Game.h"
#include "Logger.h"
#include <ctime>

Game::Game(string title, int width, int height) {
	if (Instance != nullptr) {
		exit(0);
	}
	Instance = this;

	int statusCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

	if (statusCode != 0) {
		string error = SDL_GetError();
		Logger::LogError(error);
		exit(0);
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	state = new State();
	srand(std::time(0));
}

Game* Game::Instance = nullptr;

Game::~Game() {
	delete state;
	IMG_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

Game * Game::GetInstance() {
	
	if (Instance == nullptr) {
		int width = DEFAULT_GAME_WIDTH;
		int height = DEFAULT_GAME_HEIGHT;
		return new Game("default Title", width, height);
	}

	return Instance;
}

State * Game::GetState() {
	return state;
}

SDL_Renderer * Game::GetRenderer() {
	return renderer;
}

void Game::Run() {
	while (!(*state).QuitRequested()) {

		//renderiza o novo quadro
		state->Render();
		state->Update(3.0);
		SDL_RenderPresent(renderer);

		//Delay para evitar renderização excessivas
		SDL_Delay(33);
	}
}
