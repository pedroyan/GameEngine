#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"

Vec2 Alien::defaultSpeed(500, 0);

Alien::Alien(float x, float y, int nMinions) {
	sp = (*new Sprite("img/alien.png"));

	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();

	hp = 100;

	speed = defaultSpeed;

	populateMinionArray(nMinions);
}

Alien::~Alien() {
}

void Alien::Update(float dt) {
	auto& input = InputManager::GetInstance();
	rotation -= 2*dt;
	if (input.MousePress(LEFT_MOUSE_BUTTON)) {
		taskQueue.push(Action(Action::ActionType::SHOOT, input.GetWorldMouseX(), input.GetWorldMouseY()));
	}

	if (input.IsMouseDown(RIGHT_MOUSE_BUTTON)) {
		taskQueue.push(Action(Action::ActionType::MOVE, input.GetWorldMouseX(), input.GetWorldMouseY()));
	}

	if (taskQueue.size() > 0) {

		auto action = taskQueue.front();
		if (action.type == Action::ActionType::MOVE) {
			move(dt, action);
		} else if (action.type == Action::ActionType::SHOOT) {
			auto closestMinion = getClosestMinion(action.pos);
			closestMinion->Shoot(action.pos);
			taskQueue.pop();
		}
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
	if (other.Is("Bullet")) {
		hp -= 10;
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


void Alien::move(float dt, Alien::Action action) {

	Vec2 positionVector = box.GetCenter();

	//Calcula o angulo somente 1 vez para cada novo movimento
	if (speed.Equals(defaultSpeed)) {
		auto rotationAngle = positionVector.GetDistanceVectorAngle(action.pos);
		speed.Rotate(rotationAngle);
	}

	auto realSpeed = speed * dt;

	float distanceTravelled = realSpeed.Magnitude();

	//Movimenta de acordo com a velocidade caso a distancia percorrida < distancia que falta
	float distanceToGo = positionVector.GetDistance(action.pos);
	if (distanceTravelled < distanceToGo) {
		box += realSpeed;
	} else {

		// caso a distancia percorrida pela velocidade > distancia que falta, seta a posição instantaneamente
		box.SetCenter(action.pos.X, action.pos.Y);
		taskQueue.pop();

		speed = defaultSpeed;
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


Alien::Action::Action(ActionType actionType, float x, float y) {
	type = actionType;
	pos.X = x;
	pos.Y = y;
}
