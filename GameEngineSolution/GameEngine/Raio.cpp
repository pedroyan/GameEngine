#include "Raio.h"
#include "TileCollision.h"
#include "Camera.h"
Raio::Raio(float x, float y, float angle, float speedArg, float maxDistance, string sprite, int frameCount, bool targetsPlayerv, int damage) :sp(sprite, frameCount, 0.1), speed(speedArg, 0) {
	Init(x, y, angle, maxDistance, targetsPlayerv, damage);
}

Raio::Raio(float x, float y, float angle, float speedArg, float maxDistance, Sprite & sprite, bool targetsPlayerv, int damage) : speed(speedArg, 0) {
	sp = sprite;
	Init(x, y, angle, maxDistance, targetsPlayerv, damage);
}

Raio::~Raio() {
}

void Raio::Update(float dt) {
	sp.Update(dt);
}

void Raio::Render() {
	sp.Render(box.GetWorldRenderPosition(), rotation, false, Camera::Zoom);
}

bool Raio::IsDead() {
	return sp.GetCurrentFrame() == sp.GetFrameCount()-1;
}

void Raio::NotifyCollision(GameObject & other) {
}

bool Raio::Is(string type) {
	return type == "Bolt";
}

void Raio::Init(float x, float y, float angle, float maxDistance, bool targetsPlayerv, int damage) {
	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();

	distanceLeft = maxDistance;
	speed.Rotate(angle);
	rotation = angle;
	this->damage = damage;
	targetsPlayer = targetsPlayerv;
}
