#include "Game.h"
#include "Logger.h"

Game::Game(string title, int width, int height) {
	if (Instance != nullptr) {
		throw new std::exception("Não é possivel instanciar mais de um jogo!");
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
}

Game* Game::Instance = nullptr;

Game::~Game() {
}

Game * Game::GetInstance() {
	
	if (Instance == nullptr) {
		return new Game("Default Title", 300, 300);
	}

	return Instance;
}
