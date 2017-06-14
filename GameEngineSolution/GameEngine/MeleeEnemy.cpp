#include "MeleeEnemy.h"

float attackRange = 13;

MeleeEnemy::MeleeEnemy() {
}


MeleeEnemy::~MeleeEnemy() {
}

void MeleeEnemy::Update(float dt) {
	MoveToDumbly(focus->box.GetCenter());
	if (this->focus->box.DistanceFrom(box) <= 13) {
		Attack();
	}
}

void MeleeEnemy::Render() {
}

void MeleeEnemy::NotifyCollision(GameObject & other) {
}

void MeleeEnemy::Attack() {
}
