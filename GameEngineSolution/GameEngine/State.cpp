#include "State.h"
#include "Game.h"


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
#ifdef _DEBUG
		objectArray[i]->CreateDebugBox();
#endif // _DEBUG

	}
}

TileMap State::GetMap(){
	return TileMap();
}

void State::Swap(State * state) {
	quitRequested = true;
	Game::GetInstance().Push(state);
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
