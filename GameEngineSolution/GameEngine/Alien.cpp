#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"

Vec2 Alien::defaultSpeed(20, 0);

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

	if (input.IsMouseDown(LEFT_MOUSE_BUTTON)) {
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
			taskQueue.pop();
		}
	}

	for (auto& minion : minionArray) {
		minion.Update(dt);
	}
}

void Alien::Render() {
	auto cameraPosition = Camera::pos;
	int x = box.X - cameraPosition.X;
	int y = box.Y - cameraPosition.Y;

	sp.Render(x, y);
	for (auto& minion : minionArray) {
		minion.Render();
	}
}

bool Alien::IsDead() {
	return hp <= 0;
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
	float distanceTravelled = speed.Magnitude();

	//Movimenta de acordo com a velocidade caso a distancia percorrida < distancia que falta
	float distanceToGo = positionVector.GetDistance(action.pos);
	if (distanceTravelled < distanceToGo) {

		//Calcula o angulo somente 1 vez para cada novo movimento
		if (speed.Equals(defaultSpeed)) {
			auto rotationAngle = positionVector.GetDistanceVectorAngle(action.pos);
			speed.Rotate(rotationAngle);
		}

		box.X += speed.X;
		box.Y += speed.Y;
	} else {

		// caso a distancia percorrida pela velocidade > distancia que falta, seta a posi��o instantaneamente
		box.SetCenter(action.pos.X, action.pos.Y);
		taskQueue.pop();

		speed = defaultSpeed;
	}
}


Alien::Action::Action(ActionType actionType, float x, float y) {
	type = actionType;
	pos.X = x;
	pos.Y = y;
}
