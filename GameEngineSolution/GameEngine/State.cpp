#include "State.h"



State::State() {
	popRequested = false;
	quitRequested = false;
}


State::~State() {
}

void State::UpdateArray(float dt) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
}

void State::RenderArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

void State::AddObject(GameObject * object) {
	auto uniqueObject = std::unique_ptr<GameObject>(object);
	objectArray.push_back(std::move(uniqueObject));
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}
