#include "Item.h"
#include "Debug.h"
#include "Camera.h"

Item::Item(int x,int y,ItemType tipo) {

	itemType = tipo;
	switch (tipo) {
		case ItemType::Key:
			sp = Sprite("img/itemRed.png");
			break;
		default:
			break;
	}

	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();
}


void Item::Render() {
	sp.Render(box.GetWorldRenderPosition(),0,false, Camera::Zoom);
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

ItemType Item::GetType() {
	return itemType;
}
