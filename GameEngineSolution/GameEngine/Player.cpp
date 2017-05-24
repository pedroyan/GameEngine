#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"
#include <math.h>
#include "StageState.h"
#include "TileCollision.h"

Player* Player::playerInstance = nullptr;
float acceleration = 200;
//Limite para velocidade adiante
float SpeedLimit = 400;

//cooldown de tiro em segundos
float coolDown = 0.5;

Player::Player(float x, float y) : bodySP("img/MainPlayer.png"), cannonSp("img/cubngun.png"),speed(0,0){
	rotation = 0;
	Player::playerInstance = this;
	hp = 900000;//vida alterada pra teste
	cooldownCounter = Timer();

	box.X = x;
	box.Y = y;
	box.W = bodySP.GetWidth();
	box.H = bodySP.GetHeight();
}

Player::~Player() {
	Player::playerInstance = nullptr;
}

void Player::Update(float dt) {
	auto& input = InputManager::GetInstance();
	if (cooldownCounter.Get() != 0) {
		cooldownCounter.Update(dt);
		if (cooldownCounter.Get() > 0) {
			cooldownCounter.Restart();
		}
	}

	//Rotaciona caso D ou A sejam apertados
	if (input.IsKeyDown(SDLK_d)) {
		speed.X = SpeedLimit;
	} else if (input.IsKeyDown(SDLK_a)) {
		speed.X = -SpeedLimit;
	} else {
		speed.X = 0;
	}

	applyTileEffect(dt);
	UpdateCannonAngle(input);

	if (input.MousePress(LEFT_MOUSE_BUTTON) && cooldownCounter.Get() == 0) {
		Shoot();
	}
}

void Player::Render() {
	bodySP.Render(box.GetWorldPosition(), 0);

	auto centerPosition = box.GetCenter();

	Vec2 renderPosition;
	renderPosition.X = centerPosition.X - cannonSp.GetWidth() / 2 - Camera::pos.X;
	renderPosition.Y = centerPosition.Y - cannonSp.GetHeight() / 2 - Camera::pos.Y;

	cannonSp.Render(renderPosition,cannonAngle);
}

bool Player::IsDead() {
	return hp <= 0;
}

void Player::NotifyCollision(GameObject & other) {
	if (other.Is("Bullet") && static_cast<const Bullet&>(other).targetsPlayer) {
		takeDamage(10);
	}
}

bool Player::Is(string type) {
	return type == "Penguins";
}

void Player::Shoot() {
	Vec2 cannonOffset(50, 0);
	cannonOffset.Rotate(cannonAngle);
	
	//Subtrai um Vetor(-15,15) do centro do sprite para se tornar o centro do canh�o
	Vec2 spawnPoint = box.GetCenter() + Vec2(-15,-15) + cannonOffset;

	auto bullet = new Bullet(spawnPoint.X, spawnPoint.Y, cannonAngle, getInertialBulletSpeed(), 1000, "img/penguinbullet.png",4, false);
	Game::GetInstance().GetCurrentState().AddObject(bullet);

	cooldownCounter.Update(-coolDown);
}


void Player::UpdateCannonAngle(InputManager & manager) {
	Vec2 mousePosition(manager.GetWorldMouseX(), manager.GetWorldMouseY());
	Vec2 cannonAxis = box.GetCenter();

	cannonAngle = cannonAxis.GetDistanceVectorAngle(mousePosition);
}

float Player::getInertialBulletSpeed() {
	Vec2 bulletSpeed(1000, 0);
	bulletSpeed.Rotate(cannonAngle);
	return (bulletSpeed + speed).Magnitude();
}

void Player::takeDamage(int damage) {
	hp -= damage;
	if (IsDead()) {
		Game::GetInstance().GetCurrentState().AddObject(new Animation(box.GetCenter(), rotation, "img/penguindeath.png", 5, 0.125, true));
		Sound("audio/boom.wav").Play(0);
	}
}

void Player::applyTileEffect(float dt){
	// TileCollision collisionAnalysis;
	Rect previousRect = box;
	
	//EIXO X
	box.X += speed.X*dt;//caso nao tenha colisao,aplicado a movimentacao normal em X
	auto collisionAnalysisX = TileCollision::isCollinding(this->box);
	if (collisionAnalysisX == TileCollision::Solid) {
		box.X = previousRect.X;
	}
	if (collisionAnalysisX == TileCollision::Snow) {
		box.X = box.X - (speed.X*dt / 2);
	}

	//EIXO Y
	box.Y += speed.Y*dt;//caso nao tenha colisao,aplicado a movimentacao normal em Y
	auto collisionAnalysisY = TileCollision::isCollinding(this->box);
	if (collisionAnalysisY == TileCollision::Solid) {
		box.Y = previousRect.Y;
	}
	if (collisionAnalysisY == TileCollision::Snow) {
		box.Y = box.Y - (speed.Y*dt / 2);
	}
}
