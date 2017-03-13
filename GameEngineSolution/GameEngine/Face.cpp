#include "Face.h"
#include "Game.h"

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
}

void Face::Render() {
	sp.Render(box.X, box.Y);
}

bool Face::IsDead() {
	return hitpoint <= 0;
}
