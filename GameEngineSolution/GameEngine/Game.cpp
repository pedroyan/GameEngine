#include "Game.h"
#include "Logger.h"
#include "InputManager.h"
#include <ctime>

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
	storedState = nullptr;
	srand(std::time(0));
	dt = 0;
	frameStart = 0;
}

Game* Game::Instance = nullptr;

Game::~Game() {
	if (storedState != nullptr) {
		delete storedState;
	}

	while (stateStack.size() > 0) {
		stateStack.pop();
	}

	IMG_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

Game & Game::GetInstance() {
	
	if (Instance == nullptr) {
		int width = DEFAULT_GAME_WIDTH;
		int height = DEFAULT_GAME_HEIGHT;
		return (*new Game("default Title", width, height));
	}

	return *Instance;
}

State & Game::GetCurrentState() {
	return *stateStack.top();
}

void Game::Push(State * state) {
	storedState = state;
}

SDL_Renderer * Game::GetRenderer() {
	return renderer;
}

void Game::Run() {
	if (storedState != nullptr) {
		auto uniqueObject = std::unique_ptr<State>(storedState);
		stateStack.push(std::move(uniqueObject));
		storedState = nullptr;
	} else {
		return;
	}

	while (!stateStack.empty() && !(*stateStack.top()).QuitRequested()) {
		CalculateDeltaTime();

		auto& currentState = GetCurrentState();
		//renderiza o novo quadro
		currentState.Render();
		InputManager::GetInstance().Update();
		currentState.Update(dt);
		SDL_RenderPresent(renderer);

		//printf("Mouse x: %d     Mouse Y: %d\n", InputManager::GetInstance().GetWorldMouseX(), InputManager::GetInstance().GetWorldMouseY());

		ManagePile();
		SDL_Delay(20);
	}
}

float Game::GetDeltaTime() {
	return dt;
}

void Game::CalculateDeltaTime() {
	int actualTicks = SDL_GetTicks();
	dt = (actualTicks - frameStart) / 1000.0;
	frameStart = actualTicks;
}

void Game::ManagePile() {
	if (GetCurrentState().PopRequested()) {
		stateStack.pop();
		if (!stateStack.empty()) {
			auto& state = GetCurrentState();
			state.Resume();
		}
	}

	if (storedState != nullptr) {
		if (!stateStack.empty()) {
			(*stateStack.top()).Pause();
		}
		stateStack.emplace(std::unique_ptr<State>(storedState));
		storedState = nullptr;
	}
}
