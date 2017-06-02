#include "TitleState.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"
float blinKFrequency = 3; //hz
float period = 1 / blinKFrequency;
TitleState::TitleState() : bg("img/title.jpg"), mainText("font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Pressione espaco para comecar", {255,255,255,255}), menuMusic("audio/Opening.wav") {
	mainText.SetPos(bg.GetWidth() / 2, bg.GetHeight() - 80, true, false);
	menuMusic.Play(-1);
}


TitleState::~TitleState() {
}

void TitleState::Update(float dt) {
	auto& manager = InputManager::GetInstance();
	quitRequested = manager.QuitRequested() || manager.KeyPress(SDLK_ESCAPE);
	if (manager.KeyPress(SDLK_SPACE)) {
		Game::GetInstance().Push(new StageState("map/map.tmx","img/tileset.png",2));
	}
	textTimer.Update(dt);
	if (textTimer.Get() > period) {
		textTimer.Restart();
	}
}

void TitleState::Render() {
	bg.Render(0, 0);
	if (textTimer.Get() <= period /2.0) {
		mainText.Render();
	}
	
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}
