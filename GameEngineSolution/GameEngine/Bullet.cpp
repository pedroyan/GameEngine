#include "Bullet.h"
#include "TileCollision.h"
Bullet::Bullet(float x, float y, float angle, float speedArg, float maxDistance, string sprite, int frameCount, bool targetsPlayerv,int damage):sp(sprite, frameCount,0.1),speed(speedArg,0) {
	Init(x, y, angle, maxDistance, targetsPlayerv, damage);
}

Bullet::Bullet(float x, float y, float angle, float speedArg, float maxDistance, Sprite & sprite, bool targetsPlayerv, int damage):speed(speedArg,0) {
	sp = sprite;
	Init(x, y, angle, maxDistance, targetsPlayerv, damage);
}

Bullet::~Bullet() {
}

void Bullet::Update(float dt) {
	auto realSpeed = speed * dt;
	auto bulletCenter = box.GetCenter();
	bulletCenter = bulletCenter + realSpeed;

	box.SetCenter(bulletCenter.X, bulletCenter.Y);
	distanceLeft -= realSpeed.Magnitude();
	
	auto collisionAnalysisLayer0 = TileCollision::PriorityCollision(this->box, 0);
	if (collisionAnalysisLayer0 == CollisionType::Solid) {
		distanceLeft = 0;
	}
	sp.Update(dt);
}

void Bullet::Render() {
	sp.Render(box.GetWorldRenderPosition(), rotation,false,Camera::Zoom);
}

bool Bullet::IsDead() {
	return distanceLeft <= 0;
}

void Bullet::NotifyCollision(GameObject & other) {
	if ((other.Is("Player") && targetsPlayer) || (other.IsEnemy() && !targetsPlayer) || other.Is("Barrier")) {
		distanceLeft = 0;
	}
}

bool Bullet::Is(string type) {
	return type == "Bullet";
}

void Bullet::Init(float x, float y, float angle, float maxDistance, bool targetsPlayerv, int damage) {
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
