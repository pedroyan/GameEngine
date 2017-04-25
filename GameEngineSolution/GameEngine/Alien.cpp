#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "StageState.h"
#include "Animation.h"
#include "Game.h"
#include "Bullet.h"
#include "Penguins.h"
#include <cfloat>

Vec2 Alien::defaultSpeed(500, 0);
int Alien::alienCount = 0;

const int restCooldown = 1;

Alien::Alien(float x, float y, int nMinions) : sp("img/alien.png") {
	Alien::alienCount++;
	state = Alienstate::RESTING;

	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();

	hp = 100;

	speed = defaultSpeed;

	populateMinionArray(nMinions);
}

Alien::~Alien() {
	Alien::alienCount--;
}

void Alien::Update(float dt) {
	auto& input = InputManager::GetInstance();
	rotation -= 2*dt;

	if (Penguins::player != nullptr) {
		runAI(dt);
	}

	for (auto& minion : minionArray) {
		minion.Update(dt);
	}
}

void Alien::Render() {
	auto position = box.GetWorldPosition();

	sp.Render(position, rotation);
	for (auto& minion : minionArray) {
		minion.Render();
	}
}

bool Alien::IsDead() {
	return hp <= 0;
}

bool Alien::Is(string type) {
	return type == "Alien";
}

void Alien::NotifyCollision(GameObject & other) {
	if (other.Is("Bullet") && !static_cast<const Bullet&>(other).targetsPlayer) {
		takeDamage(10);
	}
}

void Alien::populateMinionArray(int nMinions) {
	float offset = 0;
	float angularDistance = nMinions > 0 ? M_PI * 2 / nMinions : 0;

	for (int i = 0; i < nMinions; i++) {
		minionArray.emplace_back(Minion(this, offset));
		offset += angularDistance;
	}
}

/// <summary>
/// Movimenta o centro do alien para a posição indicada.
/// </summary>
/// <param name="dt">tempo decorrido entre um frame e outro</param>
/// <param name="targetPosition">posição de destina</param>
/// <returns>Indica se o movimento se encerrou</returns>
bool Alien::move(float dt, Vec2 targetPosition) {

	Vec2 positionVector = box.GetCenter();

	//Calcula o angulo somente 1 vez para cada novo movimento
	if (speed.Equals(defaultSpeed)) {
		auto rotationAngle = positionVector.GetDistanceVectorAngle(targetPosition);
		speed.Rotate(rotationAngle);
	}

	auto realSpeed = speed * dt;

	float distanceTravelled = realSpeed.Magnitude();

	//Movimenta de acordo com a velocidade caso a distancia percorrida < distancia que falta
	float distanceToGo = positionVector.GetDistance(targetPosition);
	if (distanceTravelled < distanceToGo) {
		box += realSpeed;
		return false;
	} else {

		// caso a distancia percorrida pela velocidade > distancia que falta, seta a posição instantaneamente
		box.SetCenter(targetPosition.X, targetPosition.Y);

		speed = defaultSpeed;
		return true;
	}
}

Minion* Alien::getClosestMinion(Vec2 pos) {
	
	float smallestDistance = FLT_MAX;
	Minion* closestMinion = nullptr;

	for (auto& minion : minionArray) {
		auto minionDistance = minion.box.GetCenter().GetDistance(pos);
		if (minionDistance < smallestDistance) {
			smallestDistance = minionDistance;
			closestMinion = &minion;
		}
	}

	return closestMinion;
}

void Alien::takeDamage(int damage) {
	hp -= damage;
	if (IsDead()) {
		Game::GetInstance().GetCurrentState().AddObject(new Animation(box.GetCenter(), rotation, "img/aliendeath.png", 4, 0.125, true));
		Sound("audio/boom.wav").Play(0);
	}
}

void Alien::runAI(float dt) {
	auto currentPlayerCenter = Penguins::player->box.GetCenter();
	if (state == Alienstate::RESTING) {
		restTimer.Update(dt);
		if (restTimer.Get() >= restCooldown) {
			destination = currentPlayerCenter;
			move(dt, destination);
			state = Alienstate::MOVING;
		}
	} else {
		auto concluiMovimento = move(dt, destination);
		if (concluiMovimento) {
			auto closestMinion = getClosestMinion(currentPlayerCenter);
			closestMinion->Shoot(currentPlayerCenter);
			restTimer.Restart();
			state = Alienstate::RESTING;
		}
	}
}
