#include "Face.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"

Face::Face(float x, float y){
	hitpoint = 30;
	sp = (*new Sprite("img/penguinface.png"));

	int w = sp.GetWidth();
	int h = sp.GetHeight();

	box.W = sp.GetWidth();
	box.H = sp.GetHeight();
	box.X = x - box.W / 2.0;
	box.Y = y - box.H / 2.0;
}

Face::~Face(){
}

void Face::Damage(int damage) {
	hitpoint -= damage;
}

void Face::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();
	float x = inputManager.GetMouseX() + Camera::pos.X;
	float y = inputManager.GetMouseY() + Camera::pos.Y;
 	if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && box.IsInside(x,y)) {
		Damage(rand() % 10 + 10);
	}

}

void Face::Render() {
	Vec2 cameraPosition = Camera::pos;
	int x = box.X - cameraPosition.X;
	int y = box.Y - cameraPosition.Y;

	sp.Render(x, y);
}

bool Face::IsDead() {
	return hitpoint <= 0;
}
