#include "Portal.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"

Portal::Portal(string nextMap, string nextTileSet, Rect dimensions, int nextPlayerLayer, string text) : portalText("font/Call me maybe.ttf",20,Text::TextStyle::BLENDED, text, { 0,0,0,255 }){
	box = dimensions;
	portalText.SetPos(dimensions.GetCenter().X, dimensions.Y - 20, true, false);
	this->nextMap = nextMap;
	this->nextTileSet = nextTileSet;
	this->nextPlayerLayer = nextPlayerLayer;
}

void Portal::Update(float dt) {
}

void Portal::Render() {
}

bool Portal::IsDead() {
	return false;
}

void Portal::NotifyCollision(GameObject & other) {
	if (other.Is("Player")) {
		portalText.Render(Camera::pos.X, Camera::pos.Y);
		if (InputManager::GetInstance().KeyPress(SDLK_f)) {
			Game::GetInstance().GetCurrentState().Swap(new StageState(nextMap, nextTileSet,nextPlayerLayer));
		}
	}
}

bool Portal::Is(string type) {
	return type == "Portal";
}


Portal::~Portal() {
}
