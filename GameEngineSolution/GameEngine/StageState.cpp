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
#include "XMLParser.h"
#include "Item.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"

//coolDownSpawn de tiro em segundos
const float coolDownSpawn = 3.0;

StageState::StageState(string map, string tileSet, string paralax, string music) : bg1(paralax, 0.2), stageMusic(music) {
	XMLParser parser(map);
	int th, tw;
	parser.GetTileDimensions(&th, &tw);

	this->tileSet = new TileSet(tw, th, tileSet);
	this->tileMap = TileMap(parser, this->tileSet);
	this->playerLayer = tileMap.GetPlayerLayer();

	TileCollision::GetParameters(tileMap);
	quitRequested = false;
	Player* player = nullptr;

	if (!parser.PlayerDefinedOnMap()) {
		player = new Player(704, 0);
		Camera::Follow(player);
	}

	auto objects = parser.GetMapObjects();
	for (auto& obj : objects) {
		if (obj->Is("Player")) {
			player = static_cast<Player*>(obj);
		}
		AddObject(obj);
	}

	//1122,544
	auto enemy = new MeleeEnemy(1122, 544);
	auto enemyRanged = new RangedEnemy(1160, 544);
	enemy->Focus(player);
	enemyRanged->Focus(player);
	AddObject(enemy);
	AddObject(enemyRanged);
	SpawnKeys();
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
	SpawnEnemy(dt);
}

void StageState::Render() {
	bg1.Render(Camera::pos.X, Camera::pos.Y);
	tileMap.Render(ceil(Camera::pos.X), ceil(Camera::pos.Y),0,playerLayer);
	RenderArray();
	tileMap.Render(ceil(Camera::pos.X), ceil(Camera::pos.Y),playerLayer);
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

void StageState::SpawnEnemy(float dt) {
	//int numberOfEnemys = 20;
	int numberOfEnemys = rand() % 3;
	
	coolDownSpawnCounter.Update(dt);
	if (this->coolDownSpawnCounter.Get() >coolDownSpawn) {
		for (int i = 0; i < numberOfEnemys; i++) {
			int randomEnemy = rand() % 2;
			auto spawn = tileMap.GetRandomSpawnPosition();
			
			switch (randomEnemy) {
			case 0:{
				auto enemy = new MeleeEnemy(spawn.X, spawn.Y - 64);
				enemy->Focus(Player::playerInstance);
				AddObject(enemy);
			}
				break;
			case 1:{
				auto enemy2 = new RangedEnemy(spawn.X, spawn.Y - 64);
				enemy2->Focus(Player::playerInstance);
				AddObject(enemy2);
			}
				break;
			default:
				break;
			}

			
		}
		coolDownSpawnCounter.Restart();
	}

}

void StageState::SpawnKeys() {
	for (size_t i = 0; i < 3; i++) {
		auto spawn = tileMap.GetRandomSpawnPosition();
		auto key = new Item(spawn.X, spawn.Y, ItemType::Key);
		AddObject(key);
	}
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
	delete tileSet;
}
