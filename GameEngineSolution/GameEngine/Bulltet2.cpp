#include "Bullet2.h"
#include "TileCollision.h"
#include "Game.h"
#include "Animation.h"
Bullet2::Bullet2(float x, float y, float angle, float speedArg, float maxDistance, string sprite, int frameCount, bool targetsPlayerv, int damage) :sp(sprite, frameCount, 0.1), speed(speedArg, 0) {
	Init(x, y, angle, maxDistance, targetsPlayerv, damage);
}

Bullet2::Bullet2(float x, float y, float angle, float speedArg, float maxDistance, Sprite & sprite, bool targetsPlayerv, int damage) : speed(speedArg, 0) {
	sp = sprite;
	Init(x, y, angle, maxDistance, targetsPlayerv, damage);
}

Bullet2::~Bullet2() {
}

void Bullet2::Update(float dt) {
	auto realSpeed = speed * dt;
	auto Bullet2Center = box.GetCenter();
	Bullet2Center = Bullet2Center + realSpeed;

	box.SetCenter(Bullet2Center.X, Bullet2Center.Y);
	distanceLeft -= realSpeed.Magnitude();

	auto collisionAnalysisLayer0 = TileCollision::PriorityCollision(this->box, 0);
	if (collisionAnalysisLayer0 == CollisionType::Solid) {
		
	}
	sp.Update(dt);
}

void Bullet2::Render() {
	sp.Render(box.GetWorldRenderPosition(), rotation, false, Camera::Zoom);
}

bool Bullet2::IsDead() {
	return distanceLeft <= 0;
}

void Bullet2::NotifyCollision(GameObject & other) {
	if ((other.Is("Player") && targetsPlayer) || (other.IsEnemy() && !targetsPlayer) || other.Is("Barrier")) {
	

	}
}

bool Bullet2::Is(string type) {
	return type == "Bullet";
}

void Bullet2::Init(float x, float y, float angle, float maxDistance, bool targetsPlayerv, int damage) {
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
