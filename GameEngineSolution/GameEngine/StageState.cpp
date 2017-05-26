#include "StageState.h"
#include <vector>
#include "Camera.h"
#include <SDL.h>
#include <math.h>
#include "InputManager.h"
#include "Alien.h"
#include "Player.h"
#include "Collision.h"
#include "Game.h"
#include "EndState.h"
#include "TileCollision.h"

StageState::StageState() : tileSet(64,64,"img/tileset.png"), bg1("img/back1.png", 0.2), stageMusic("audio/stageState.ogg") {
	this->tileMap = TileMap("map/map.tmx", &tileSet);
	TileCollision::GetParameters(tileMap);
	quitRequested = false;
	stageMusic.Play(-1);

	auto player = new Player(704, 1000);
	Camera::Follow(player);
	AddObject(player);

}

void StageState::LoadAssets() {
}

void StageState::Update(float dt) {
	Camera::Update(dt);
	auto& manager = InputManager::GetInstance();

	popRequested = manager.KeyPress(SDLK_ESCAPE);
	quitRequested = manager.QuitRequested();

	UpdateArray(dt);

	if (false) {
		popRequested = true;
		Game::GetInstance().Push(new EndState(StateData(true)));
	} else if (Player::playerInstance == nullptr) {
		popRequested = true;
		Game::GetInstance().Push(new EndState(StateData(false)));
	}
}

void StageState::Render() {
	bg1.Render(Camera::pos.X, Camera::pos.Y);
	tileMap.Render(ceil(Camera::pos.X), ceil(Camera::pos.Y));
	RenderArray();
}

void StageState::Pause() {
}

void StageState::Resume() {
}

TileMap StageState::GetMap(){
	return tileMap;
}

void StageState::AddObject(GameObject * ptr) {
	auto uniqueObject = std::unique_ptr<GameObject>(ptr);
	objectArray.push_back(std::move(uniqueObject));
}

void StageState::CheckCollisions() {
	auto size = objectArray.size();
	for (size_t i = 0; i < size; i++) {
		if (!objectArray[i]->Is("Animation")) {
			for (size_t j = i + 1; j < size; j++) {
				if (!objectArray[j]->Is("Animation") && Collision::IsColliding(objectArray[i]->box, objectArray[j]->box, objectArray[i]->rotation, objectArray[j]->rotation)) {
					objectArray[i]->NotifyCollision(*objectArray[j]);
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}
			}
		}
	}
}

void StageState::UpdateArray(float dt) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

	CheckCollisions();

	for (unsigned i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
}


StageState::~StageState() {
	objectArray.clear();
}
