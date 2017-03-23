#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle, float speedArg, float maxDistance, string sprite):sp(sprite),speed(speedArg,0) {
	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();

	distanceLeft = maxDistance;
	speed.Rotate(angle);
}

Bullet::~Bullet() {
}

void Bullet::Update(float dt) {
	auto realSpeed = speed * dt;
	box += realSpeed;

	distanceLeft -= realSpeed.Magnitude();
}

void Bullet::Render() {
	int x = box.X - Camera::pos.X;
	int y = box.Y - Camera::pos.Y;

	sp.Render(x, y);
}

bool Bullet::IsDead() {
	return distanceLeft <= 0;
}
