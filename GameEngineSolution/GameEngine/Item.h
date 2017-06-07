#pragma once
#include "GameObject.h"
#include "Sprite.h"
class Item : public GameObject {
	public:
	enum ItemType {//quanto maior o enum,maior a prioridade da colissao
		Red = 0,
		Green,
		Blue
	}type;
	Item(int x, int y, ItemType tipo);
	Item(int x, int y);
	void Render();
	void Update(float dt);
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	~Item();
	void CreateDebugBox();

	private:
	bool isTaken=false;
	Sprite sp;
};

