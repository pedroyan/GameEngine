#include "Portal.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Player.h"

const float animationTime = 1.0;

Portal::Portal(string nextMap, string nextTileSet, Rect dimensions, string text) : displayText("font/Call me maybe.ttf", 20, Text::TextStyle::BLENDED, text, { 0,0,0,255 }),
sp("img/Portal.png", 6, animationTime / 6, true) {
	box = dimensions;
	this->nextMap = nextMap;
	this->nextMusic = "audio/fase1.wav";
	this->nextTileSet = nextTileSet;
	this->text = text;
	OpenRequested = false;
	CenterDisplayText();
}

void Portal::Update(float dt) {
	if (OpenRequested) {
		sp.Update(dt);
		teleportTime.Update(dt);
		if (teleportTime.Get() >= animationTime) {
			auto& stageState = static_cast<StageState&>(Game::GetInstance().GetCurrentState());
			stageState.Swap(new StageState(nextMap, nextTileSet, nextMusic));
		}
	}
}

void Portal::Render() {
	if (OpenRequested) {
		sp.Render(box.GetWorldRenderPosition(), 0, false, Camera::Zoom);
	}
}

bool Portal::IsDead() {
	return false;
}

void Portal::NotifyCollision(GameObject & other) {
	//Esse downcast não é lá das melhores idéias. Mas como estamos apertados com o prazo
	//e até agora só existe portal se existir StageState, posso SEMPRE fazer o downcast,
	//pois para o PORTAL estar presente no jogo, um StageState deve estar presente.

	if (other.Is("Player")) {
		auto& manager = InputManager::GetInstance();
		auto& stageState = static_cast<StageState&>(Game::GetInstance().GetCurrentState());
		if (stageState.GetHordeMode()) {
			auto& player = static_cast<const Player&>(other);
			if (player.GetKeyCount() < 3) {
				auto keysLeft = 3 - player.GetKeyCount();
				UpdateText("Faltam " + std::to_string(keysLeft) + " chaves");
			} else {
				UpdateText(this->text);
				if (InputManager::GetInstance().KeyPress(SDLK_f)) {
					OpenRequested = true;
				}
			}
		} else {
			UpdateText(this->text);
			if (manager.KeyPress(SDLK_f)) {
				stageState.EnableHordeMode();
			}
		}
		
	}
}

bool Portal::Is(string type) {
	return type == "Portal";
}


Portal::~Portal() {
}

void Portal::CenterDisplayText() {
	displayText.SetPos(box.GetCenter().X, box.Y - 20, true, false);
}

void Portal::UpdateText(string text) {
	displayText.SetText(text);
	CenterDisplayText();
	displayText.Render(Camera::pos.X, Camera::pos.Y, Camera::Zoom);
}
