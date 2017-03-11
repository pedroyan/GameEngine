#include "State.h"
#include <SDL.h>


State::State() {
	quitRequested = false;
	bg = new Sprite("img/ocean.jpg");
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Update(float dt) {
	quitRequested = SDL_QuitRequested();
}

void State::Render() {
	bg->Render(0, 0);
}


State::~State() {
}
