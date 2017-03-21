#include "Alien.h"
#include "InputManager.h"

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
		taskQueue.push(Action(Action::ActionType::MOVE, input.GetMouseX(), input.GetMouseY()));
	}

	if (input.IsMouseDown(RIGHT_MOUSE_BUTTON)) {
		taskQueue.push(Action(Action::ActionType::MOVE, input.GetMouseX(), input.GetMouseY()));
	}

	if (taskQueue.size() > 0) {

		auto action = taskQueue.front();
		if (action.type == Action::ActionType::MOVE) {
			move(dt, action);
		} else if (action.type == Action::ActionType::SHOOT) {
			taskQueue.pop();
		}
	}
}

void Alien::Render() {
	sp.Render(box.X, box.Y);
	for (auto& minion : minionArray) {
		minion.Render();
	}
}

bool Alien::IsDead() {
	return hp <= 0;
}

void Alien::populateMinionArray(int nMinions) {
}


void Alien::move(float dt, Alien::Action action) {

	Vec2 positionVector = Vec2(box.X, box.Y);
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

		// caso a distancia percorrida pela velocidade > distancia que falta, seta a posição instantaneamente
		box.Y = action.pos.Y;
		box.X = action.pos.X;
		taskQueue.pop();

		speed = defaultSpeed;
	}
}


Alien::Action::Action(ActionType actionType, float x, float y) {
	type = actionType;
	pos.X = x;
	pos.Y = y;
}
