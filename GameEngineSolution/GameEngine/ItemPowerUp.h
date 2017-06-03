#pragma once
#include "GameObject.h"
#include "Sprite.h"
class ItemPowerUp : public GameObject {
	public:
	enum ItemType {//quanto maior o enum,maior a prioridade da colissao
		Red = 0,
		Green,
		Blue
	}type;
	ItemPowerUp(int x, int y, ItemType tipo);
	void Render();
	void Update(float dt);
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	~ItemPowerUp();

	private:
	bool isTaked=false;
	Sprite sp;
};

