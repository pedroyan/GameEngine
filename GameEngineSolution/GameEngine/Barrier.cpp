#include "Barrier.h"
#include "Camera.h"
#include <math.h>
#include "Player.h"

float barrierPeriod = 0.25;
Barrier::Barrier(int hp, Rect box) : fullHp("img/Laser_100.png",2,barrierPeriod),
	midHp("img/Laser_66.png",2,barrierPeriod), lowHp("img/Laser_33.png",2,barrierPeriod),
	dead("img/Laser_0.png"){

	this->box = box;
	this->hp = hp;
	fullHealth = hp;

	currentSp = fullHp;
}	

void Barrier::Update(float dt) {
	currentSp.Update(dt);
	frameDt = dt;
}

void Barrier::Render() {
	currentSp.Render(box.GetWorldRenderPosition(), 0, false, Camera::Zoom);
}

bool Barrier::IsDead() {
	return hp < 0;
}

void Barrier::NotifyCollision(GameObject & other) {
	if (other.Is("Bullet")) {
		takeDamage(other.damage);
	} else if (other.Is("Player")) {
		auto player = static_cast<Player*>(&other);
		Vec2 returnSpeed = player->Speed;
		returnSpeed.Rotate(M_PI);
		returnSpeed.Y = 0;

		player->box += returnSpeed*frameDt;
	}
}

bool Barrier::Is(string type) {
	return type == "Barrier";
}

Barrier::~Barrier() {
}

void Barrier::takeDamage(int dam) {
	hp -= dam;
	float actualPercentage = (float)hp / (float)fullHealth;
	if (actualPercentage < 0) {
		currentSp = dead;
	} else if (actualPercentage <= 0.33) {
		currentSp = lowHp;
	} else if(actualPercentage <= 0.66) {
		currentSp = midHp;
	}
}
