#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"


EndState::EndState(StateData stateData) : instruction("font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Esc para menu, Espaco para tentar novamente", { 255,255,255,255 }),
bg(stateData.playerVictory ? "img/win.jpg" : "img/lose.jpg"),
music(stateData.playerVictory ? "audio/endStateWin.ogg" : "audio/endStateLose.ogg") 
{
	instruction.SetPos(bg.GetWidth() / 2, bg.GetHeight() - 80, true, false);
	music.Play(-1);
}

EndState::~EndState() {
}

void EndState::Update(float dt) {
	auto& manager = InputManager::GetInstance();
	auto scapePressed = manager.KeyPress(SDLK_ESCAPE);
	auto spacePressed = manager.KeyPress(SDLK_SPACE);

	quitRequested = manager.QuitRequested() || scapePressed;
	popRequested = scapePressed || spacePressed;

	if (spacePressed) {
		Game::GetInstance().Push(new StageState());
	}
}

void EndState::Render() {
	bg.Render(0, 0);
	instruction.Render();
}

void EndState::Pause() {
}

void EndState::Resume() {
}
