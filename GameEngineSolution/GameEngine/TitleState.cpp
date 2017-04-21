#include "TitleState.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"

TitleState::TitleState() : bg("img/title.jpg") {
}


TitleState::~TitleState() {
}

void TitleState::Update(float dt) {
	auto& manager = InputManager::GetInstance();
	quitRequested = manager.QuitRequested() || manager.KeyPress(SDLK_ESCAPE);
	if (manager.KeyPress(SDLK_SPACE)) {
		Game::GetInstance().Push(new StageState());
	}
}

void TitleState::Render() {
	bg.Render(0, 0);
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}
