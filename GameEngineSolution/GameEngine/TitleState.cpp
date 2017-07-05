#include "TitleState.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"
float blinKFrequency = 1; //hz
float period = 1 / blinKFrequency;
TitleState::TitleState() : bg1("img/title.png"), bg2("img/title2.png"), mainText("font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Pressione espaco para comecar", {0,0,0,255}), menuMusic("audio/Opening.wav") {
	mainText.SetPos(bg1.GetWidth() / 2, bg1.GetHeight() - 80, true, false);
	menuMusic.Play(-1);
}


TitleState::~TitleState() {
}

void TitleState::Update(float dt) {
	auto& manager = InputManager::GetInstance();
	quitRequested = manager.QuitRequested() || manager.KeyPress(SDLK_ESCAPE);
	if (manager.KeyPress(SDLK_SPACE)) {
		Game::GetInstance().Push(new StageState("map/map.tmx","img/tileset.png"));
	}
	textTimer.Update(dt);
	if (textTimer.Get() > period) {
		textTimer.Restart();
	}
}

void TitleState::Render() {
	bg1.Render(0, 0);
	if (textTimer.Get() <= period /2.0) {
		bg2.Render(0, 0);
	}
	mainText.Render();
	
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}
