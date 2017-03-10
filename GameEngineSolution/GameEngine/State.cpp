#include "State.h"
#include <SDL.h>


State::State() {
	quitRequested = false;
	//instancia um sprite;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Update(float dt) {
	quitRequested = SDL_QuitRequested();
}

void State::Render() {
	//renderize o fundo (bg, tipo sprite) de forma a preencher a tela.
}


State::~State() {
}
