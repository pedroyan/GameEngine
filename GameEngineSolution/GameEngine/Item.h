#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include <string>

using std::string;

enum class ItemType {
	Key
};

class Item : public GameObject {
	public:
		Item(int x, int y, ItemType tipo);
		void Render();
		void Update(float dt);
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);
		~Item();
		void CreateDebugBox();
		ItemType GetType();

	private:
		bool isTaken=false;
		Sprite sp;
		ItemType itemType;
};

