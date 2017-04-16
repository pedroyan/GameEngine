#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle, float speedArg, float maxDistance, string sprite, int frameCount):sp(sprite, frameCount,0.1),speed(speedArg,0) {
	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();

	distanceLeft = maxDistance;
	speed.Rotate(angle);
	rotation = angle;
}

Bullet::~Bullet() {
}

void Bullet::Update(float dt) {
	auto realSpeed = speed * dt;
	auto bulletCenter = box.GetCenter();
	bulletCenter = bulletCenter + realSpeed;

	box.SetCenter(bulletCenter.X, bulletCenter.Y);
	distanceLeft -= realSpeed.Magnitude();
	sp.Update(dt);
}

void Bullet::Render() {
	sp.Render(box.GetWorldPosition(), rotation);
}

bool Bullet::IsDead() {
	return distanceLeft <= 0;
}

void Bullet::NotifyCollision(GameObject & other) {
	distanceLeft = 0;
}

bool Bullet::Is(string type) {
	return type == "Bullet";
}
