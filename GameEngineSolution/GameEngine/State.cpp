#include "State.h"
#include <vector>
#include "Camera.h"
#include <SDL.h>
#include <math.h>
#include "InputManager.h"
#include "Alien.h"


State::State() : bg("img/ocean.jpg"), tileSet(64,64,"img/tileset.png"), tileMap("map/tileMap.txt",&tileSet)  {
	quitRequested = false;
	objectArray.emplace_back(new Alien(512, 300, 3));
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::LoadAssets() {
}

void State::Update(float dt) {
	Camera::Update(dt);
	auto& manager = InputManager::GetInstance();

	quitRequested = manager.QuitRequested() || manager.KeyPress(SDLK_ESCAPE);

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
		if (objectArray[i] -> IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::Render() {
	bg.Render(0, 0);
	tileMap.Render(ceil(Camera::pos.X), ceil(Camera::pos.Y));
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

void State::AddObject(GameObject * ptr) {
	auto uniqueObject = std::unique_ptr<GameObject>(ptr);
	objectArray.push_back(std::move(uniqueObject));
}


State::~State() {
	objectArray.clear();
}
