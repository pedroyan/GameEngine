#include "Item.h"
#include "Debug.h"
#include "Camera.h"

Item::Item(int x,int y,ItemType tipo) {
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
	this->type = tipo;
}
Item::Item(int x, int y) {
	int randomItem = rand() % 3;
	switch (randomItem) {
	case Red:
		sp = Sprite("img/itemRed.png");
		this->type =Red;
		break;
	case Blue:
		sp = Sprite("img/itemBlue.png");
		this->type = Blue;
		break;
	case Green:
		sp = Sprite("img/itemGreen.png");
		this->type = Green;
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

void Item::Render() {
	sp.Render(box.GetWorldPosition(),0,false, Camera::Zoom);
}

void Item::Update(float dt) {
}

bool Item::IsDead() {
	return isTaken;
}

void Item::NotifyCollision(GameObject & other) {
	if (other.Is("Player")) {
		isTaken = true;
	}
}

bool Item::Is(string type) {
	return type == "Item";
}

Item::~Item() {
}
void Item::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box,{ 255, 239, 22});
	
}