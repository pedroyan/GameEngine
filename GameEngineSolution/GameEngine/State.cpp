#include "State.h"
#include <vector>
#include "Camera.h"
#include <SDL.h>
#include <math.h>
#include "InputManager.h"
#include "Alien.h"
#include "Penguins.h"
#include "Collision.h"


State::State() : tileSet(64,64,"img/tileset.png"), tileMap("map/tileMap.txt",&tileSet), bg("img/ocean.jpg") {
	quitRequested = false;
	objectArray.emplace_back(new Alien(512, 300, 3));
	auto penguim = new Penguins(704, 640);
	Camera::Follow(penguim);
	AddObject(penguim);

}

bool State::QuitRequested() {
	return quitRequested;
}

void State::LoadAssets() {
}

void State::Update(float dt) {
	SDL_Event event;
	Camera::Update(dt);
	auto& manager = InputManager::GetInstance();

	quitRequested = manager.QuitRequested() || manager.KeyPress(SDLK_ESCAPE);

	if (manager.KeyPress(SDLK_SPACE)) {
		Vec2 cameraPosition = Camera::pos;

		float x = (float)manager.GetMouseX() + cameraPosition.X;
		float y = (float)manager.GetMouseY() + cameraPosition.Y;

		//AddObject(x, y);
	}

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

void State::CheckCollisions() {
	auto size = objectArray.size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i+1; j < size; j++) {
			if (Collision::IsColliding(objectArray[i]->box, objectArray[j]->box, objectArray[i]->rotation, objectArray[j]->rotation)) {
				objectArray[i]->NotifyCollision(*objectArray[j]);
				objectArray[j]->NotifyCollision(*objectArray[i]);
			}
		}
	}
}


State::~State() {
	objectArray.clear();
}
