#include "ItemPowerUp.h"

ItemPowerUp::ItemPowerUp(int x,int y,ItemType tipo) {
	switch (tipo) {
	case Red:
		sp=Sprite("img/itemRed.png");
		break;
	case Blue:
		sp = Sprite("img/itemBlue.png");
		break;
	case Green:
		sp = Sprite("img/itemGreen.png");
		break;
	default:
		sp = Sprite("img/itemBlue.png");
		break;
	}
	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();
}

void ItemPowerUp::Render() {
}

void ItemPowerUp::Update(float dt) {
}

bool ItemPowerUp::IsDead() {
	return isTaked;
}

void ItemPowerUp::NotifyCollision(GameObject & other) {
	if (other.Is("Player")) {
		isTaked = true;
	}
}

bool ItemPowerUp::Is(string type) {
	return type == "ItemPowerUp";
}

ItemPowerUp::~ItemPowerUp() {
}
