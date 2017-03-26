#include "Penguins.h"
#include "InputManager.h"
#include <math.h>

Penguins* Penguins::player = nullptr;
float acceleration = 30;
//Limite para velocidade adiante
float fSpeedLimit = 200;
//Limite para velocidade de ré
float bSpeedLimit = -100;
//Velocidade angular de virara
float turningSpeed = M_PI / 16;

Penguins::Penguins(float x, float y) : bodySP("img/penguin.png"), cannonSp("img/cubngun.png"),speed(200,0){
	rotation = 0;
	Penguins::player = this;

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

	if (input.IsKeyDown(SDLK_d)) {
		rotation += turningSpeed;
		speed.Rotate(turningSpeed);
	} else if (input.IsKeyDown(SDLK_a)) {
		rotation -= turningSpeed;
		speed.Rotate(-turningSpeed);
	}

	if (input.IsKeyDown(SDLK_w) && linearSpeed < fSpeedLimit) {
		Accelerate(true, dt);
	} else if (input.IsKeyDown(SDLK_s) && linearSpeed > bSpeedLimit) {
		Accelerate(false, dt);
	}

	box += speed*dt;
}

void Penguins::Render() {
}

bool Penguins::IsDead() {
	return false;
}

void Penguins::Shoot() {
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
			? realAcceletarion								//desacelera a velocidade pela constante completa
			: -(bSpeedLimit - linearSpeed);		//caso contrário, só desacelera oque falta para a velocidade atingir o limite inferior
	}

	//Lembrando que accelarationValue é sempre positivo. Quem irá dizer
	//sua orientação é o vetor

	Vec2 accelerationVector(accelarationValue, 0);

	linearSpeed = forward ? linearSpeed + accelarationValue : linearSpeed - accelarationValue;
	auto accAngle = forward ? speed.GetXAxisAngle() : M_PI + speed.GetXAxisAngle();

	accelerationVector.Rotate(accAngle);
	speed = accelerationVector + speed;
}
