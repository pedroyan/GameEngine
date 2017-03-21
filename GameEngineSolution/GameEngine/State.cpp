#include "State.h"
#include "Face.h"
#include <vector>
#include "Camera.h"
#include <SDL.h>
#include <math.h>
#include "InputManager.h"


State::State() : tileSet(64,64,"img/tileset.png"), tileMap("map/tileMap.txt",&tileSet), bg("img/ocean.jpg") {
	quitRequested = false;
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

		AddObject(x, y);
	}

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

void State::AddObject(float mouseX, float mouseY) {
	Vec2 vec(200, 0);
	vec.Rotate(rand());
	objectArray.emplace_back(new Face(mouseX + vec.X, mouseY + vec.Y));
}


State::~State() {
	objectArray.clear();
}
