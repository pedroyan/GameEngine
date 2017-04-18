#include "Minion.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#include <math.h>
#include <random>

float Minion::angularSpeed = M_PI; //radianos/s

Minion::Minion(GameObject * minionCenter, float arcOffset) : sp("img/minion.png") {
	center = minionCenter;
	arc = arcOffset;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(1, 1.5);

	sp.SetScaleX(dis(gen));
	sp.SetScaleY(dis(gen));
}

Minion::~Minion() {
}

void Minion::Update(float dt) {
	arc += angularSpeed*dt;

	Vec2 minionCircumference(100, 0);
	minionCircumference.Rotate(arc);
	rotation = arc;

	auto centerVector = center->box.GetCenter();

	float X = centerVector.X + minionCircumference.X;
	float Y = centerVector.Y + minionCircumference.Y;
	box.SetCenter(X, Y);
}

void Minion::Render() {
	sp.Render(box.GetWorldPosition(), rotation);
}

bool Minion::IsDead() {
	return false;
}

void Minion::Shoot(Vec2 pos) {
	auto position = box.GetCenter();

	auto angle = position.GetDistanceVectorAngle(pos);
	auto bullet = new Bullet(position.X, position.Y, angle, 1000, 1000, "img/minionbullet2.png",3,true);

	auto state = Game::GetInstance()->GetState();
	state->AddObject(bullet);
}

void Minion::NotifyCollision(GameObject & other) {
	center->NotifyCollision(other);
}

bool Minion::Is(string type) {
	return type == "Minion";
}
