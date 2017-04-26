#include "Penguins.h"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"
#include <math.h>

Penguins* Penguins::player = nullptr;
float acceleration = 200;
//Limite para velocidade adiante
float fSpeedLimit = 400;
//Limite para velocidade de ré
float bSpeedLimit = -300;
//Velocidade angular de virara
float turningSpeed = M_PI / 16;

//cooldown de tiro em segundos
float coolDown = 0.5;

Penguins::Penguins(float x, float y) : bodySP("img/penguin.png"), cannonSp("img/cubngun.png"),speed(0,0){
	rotation = 0;
	Penguins::player = this;
	hp = 100;
	cooldownCounter = Timer();

	box.X = x;
	box.Y = y;
	box.W = bodySP.GetWidth();
	box.H = bodySP.GetHeight();

}

Penguins::~Penguins() {
	Penguins::player = nullptr;
}

void Penguins::Update(float dt) {
	auto& input = InputManager::GetInstance();
	if (cooldownCounter.Get() != 0) {
		cooldownCounter.Update(dt);
		if (cooldownCounter.Get() > 0) {
			cooldownCounter.Restart();
		}
	}

	//Rotaciona caso D ou A sejam apertados
	if (input.IsKeyDown(SDLK_d)) {
		rotation += turningSpeed;
		speed.Rotate(turningSpeed);
	} else if (input.IsKeyDown(SDLK_a)) {
		rotation -= turningSpeed;
		speed.Rotate(-turningSpeed);
	}

	//Acelera caso W ou S sejam apertados
	if (input.IsKeyDown(SDLK_w) && linearSpeed < fSpeedLimit) {
		Accelerate(true, dt);
	} else if (input.IsKeyDown(SDLK_s) && linearSpeed > bSpeedLimit) {
		Accelerate(false, dt);
	}
	Rect previousRect = box;
	box += speed*dt;

	if (box.X < 0 || box.X > 1408) {
		box.X = previousRect.X;
	}
	if (box.Y < 0 || box.Y > 1280) {
		box.Y = previousRect.Y;
	}

	UpdateCannonAngle(input);

	if (input.MousePress(LEFT_MOUSE_BUTTON) && cooldownCounter.Get() == 0) {
		Shoot();
	}
}

void Penguins::Render() {
	bodySP.Render(box.GetWorldPosition(), rotation);

	auto centerPosition = box.GetCenter();

	Vec2 renderPosition;
	renderPosition.X = centerPosition.X - cannonSp.GetWidth() / 2 - Camera::pos.X;
	renderPosition.Y = centerPosition.Y - cannonSp.GetHeight() / 2 - Camera::pos.Y;

	cannonSp.Render(renderPosition,cannonAngle);
}

bool Penguins::IsDead() {
	return hp <= 0;
}

void Penguins::NotifyCollision(GameObject & other) {
	if (other.Is("Bullet") && static_cast<const Bullet&>(other).targetsPlayer) {
		takeDamage(10);
	}
}

bool Penguins::Is(string type) {
	return type == "Penguins";
}

void Penguins::Shoot() {
	Vec2 cannonOffset(50, 0);
	cannonOffset.Rotate(cannonAngle);
	
	//Subtrai um Vetor(-15,15) do centro do sprite para se tornar o centro do canhão
	Vec2 spawnPoint = box.GetCenter() + Vec2(-15,-15) + cannonOffset;

	auto bullet = new Bullet(spawnPoint.X, spawnPoint.Y, cannonAngle, getInertialBulletSpeed(), 1000, "img/penguinbullet.png",4, false);
	Game::GetInstance().GetCurrentState().AddObject(bullet);

	cooldownCounter.Update(-coolDown);
}

void Penguins::Accelerate(bool forward, float dt) {
	float accelarationValue = 0;
	auto realAcceletarion = acceleration*dt;
	if (forward) {
		auto newLinearSpeed = linearSpeed + realAcceletarion;
		accelarationValue = newLinearSpeed < fSpeedLimit // mesmo raciocinio explicado na desaceleração
			? realAcceletarion
			: fSpeedLimit - linearSpeed;
	} else {
		auto newLinearSpeed = linearSpeed - realAcceletarion;
		accelarationValue = newLinearSpeed > bSpeedLimit //se a nova velocidade linear não for menor do que o limite inferior
			? realAcceletarion							//desacelera a velocidade pela constante completa
			: -(bSpeedLimit - linearSpeed);		//caso contrário, só desacelera oque falta para a velocidade atingir o limite inferior
	}

	//Lembrando que accelarationValue é sempre positivo. Quem irá dizer
	//sua orientação é o vetor

	Vec2 accelerationVector(accelarationValue, 0);

	linearSpeed = forward ? linearSpeed + accelarationValue : linearSpeed - accelarationValue;
	auto accAngle = forward ? rotation : M_PI + rotation;
	accelerationVector.Rotate(accAngle);
	speed = accelerationVector + speed;
}

void Penguins::UpdateCannonAngle(InputManager & manager) {
	Vec2 mousePosition(manager.GetWorldMouseX(), manager.GetWorldMouseY());
	Vec2 cannonAxis = box.GetCenter();

	cannonAngle = cannonAxis.GetDistanceVectorAngle(mousePosition);
}

float Penguins::getInertialBulletSpeed() {
	Vec2 bulletSpeed(800, 0);
	bulletSpeed.Rotate(cannonAngle);
	return (bulletSpeed + speed).Magnitude();
}

void Penguins::takeDamage(int damage) {
	hp -= damage;
	if (IsDead()) {
		Game::GetInstance().GetCurrentState().AddObject(new Animation(box.GetCenter(), rotation, "img/penguindeath.png", 5, 0.125, true));
		Sound("audio/boom.wav").Play(0);
	}
}
