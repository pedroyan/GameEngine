#include "Face.h"


Face::Face(float x, float y){
	hitpoint = 30;
	sp = new Sprite("img/penguinface.png");
}

Face::~Face(){
}

void Face::Damage(int damage) {
}

void Face::Update(float dt) {
}

void Face::Render() {
}

bool Face::IsDead() {
	return false;
}
