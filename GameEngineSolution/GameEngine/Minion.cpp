#include "Minion.h"
#include "Camera.h"
#include <math.h>

float Minion::angularSpeed = M_PI; //radianos/s

Minion::Minion(GameObject * minionCenter, float arcOffset) : sp("img/minion.png") {
	center = minionCenter;
	arc = arcOffset;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();
}

Minion::~Minion() {
}

void Minion::Update(float dt) {
	arc += angularSpeed*dt;

	Vec2 minionCircumference(100, 0);
	minionCircumference.Rotate(arc);

	auto centerVector = center->box.GetCenter();

	float X = centerVector.X + minionCircumference.X;
	float Y = centerVector.Y + minionCircumference.Y;
	box.SetCenter(X, Y);
}

void Minion::Render() {
	int x = box.X - Camera::pos.X;
	int y = box.Y - Camera::pos.Y;

	sp.Render(x, y);
}

bool Minion::IsDead() {
	return false;
}

void Minion::Shoot(Vec2 pos) {
	//pew pew
}
