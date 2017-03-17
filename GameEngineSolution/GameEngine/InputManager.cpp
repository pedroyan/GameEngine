#include "InputManager.h"
#include <SDL.h>


InputManager::InputManager() {
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
	quitRequested = false;
	for(auto& valor : mouseState) {
		valor = false;
	}

	for (auto& valor : mouseUpdate) {
		valor = 0;
	}
}


InputManager::~InputManager() {
}

bool InputManager::QuitRequested() {
	return quitRequested;
}

InputManager& InputManager::GetInstance() {
	static InputManager inst;
	return inst;
}

void InputManager::Update() {
	SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
			case SDL_QUIT:
				quitRequested = true;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button]++;
				break;

			case SDL_MOUSEBUTTONUP:	
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button]++;
				break;

			case SDL_KEYDOWN:
				if (!event.key.repeat) {
					auto keyPressed = event.key.keysym.sym;

					keyState[keyPressed] = true;

					int& keyCounter = keyUpdate[keyPressed];
					keyCounter++;
				}
				break;

			case SDL_KEYUP:
				auto keyPressed = event.key.keysym.sym;
				keyState[keyPressed] = false;

				int& keyCounter = keyUpdate[keyPressed];
				keyCounter++;
				break;

			default:
				break;
		}	
	}
}

bool InputManager::KeyPress(int key) {
	return keyState[key] && keyUpdate[key] == 1;
}

bool InputManager::KeyRelease(int key) {
	return !keyState[key] && keyUpdate[key] == 1;
}

bool InputManager::IsKeyDown(int key) {
	return keyState[key];
}

bool InputManager::MousePress(int button) {
	return mouseState[button] && mouseUpdate[button] == 1;
}

bool InputManager::MouseRelease(int button) {
	return !mouseState[button] && mouseUpdate[button] == 1;
}

bool InputManager::IsMouseDown(int button) {
	return mouseState[button];
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}
