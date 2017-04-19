#include "State.h"



State::State() {
	popRequested = false;
	quitRequested = false;
}


State::~State() {
}

void State::UpdateArray(float dt) {
}

void State::RenderArray() {
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
