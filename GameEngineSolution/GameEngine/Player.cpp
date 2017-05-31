#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"
#include <math.h>
#include "StageState.h"
#include "TileCollision.h"

Player* Player::playerInstance = nullptr;
//Limite para velocidade adiante
const float SpeedLimit = 400;

const float jumpHeight = 2; // em blocos
const float Gravity = 2 * 9.8;

//cooldown de tiro em segundos
const float coolDown = 0.5;

Player::Player(float x, float y) : bodySP("img/MainPlayer.png"), bodyRunSP("img/MainPlayerRun.png", 6, 0.1), cannonSp("img/cubngun.png"),speed(0,0){
	rotation = 0;
	Player::playerInstance = this;
	hp = 900000;//vida alterada pra teste
	cooldownCounter = Timer();

	box.X = x;
	box.Y = y;
	box.W = bodySP.GetWidth();
	box.H = bodySP.GetHeight();

	jumpCount = 0;
}

Player::~Player() {
	Player::playerInstance = nullptr;
}

void Player::Update(float dt) {
	auto& input = InputManager::GetInstance();
	float previousX;
	bodyRunSP.Update(dt);
	if (cooldownCounter.Get() != 0) {
		cooldownCounter.Update(dt);
		if (cooldownCounter.Get() > 0) {
			cooldownCounter.Restart();
		}
	}

	//Rotaciona caso D ou A sejam apertados
	if (input.IsKeyDown(SDLK_d)) {
		speed.X = SpeedLimit;
		movedLeft = false;
	} else if (input.IsKeyDown(SDLK_a)) {
		speed.X = -SpeedLimit;
		movedLeft = true;
	} else {
		speed.X = 0;
	}
	
	if (input.IsKeyDown(SDLK_w)) {
		speedStairs.Y = -SpeedLimit/2;
	} else if (input.IsKeyDown(SDLK_s)) {
		speedStairs.Y = +SpeedLimit/2;
	} else {
		speedStairs.Y = 0;
	}
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	if (input.KeyPress(SDLK_SPACE) && jumpCount <2) {
		auto k1 = 2 * Gravity * jumpHeight;
		speed.Y = -tileHeight *sqrt(k1);
		jumpCount++;
	} else {
		speed.Y += tileHeight * Gravity*dt;
	}

	previousX = box.X;
	Move(dt);
	deltaX = box.X - previousX;

	UpdateCannonAngle(input);

	if (input.MousePress(LEFT_MOUSE_BUTTON) && cooldownCounter.Get() == 0) {
		Shoot();
	}
}

void Player::Render() {
	auto& input = InputManager::GetInstance();
	
	if(currentLayer == 0) {
		if ((input.IsKeyDown(SDLK_d) || input.IsKeyDown(SDLK_a))  ) {//&& deltaX!=0d
			UpdateSP(bodyRunSP);
			UpdateBoxSP(bodyRunSP);
		} else {
			UpdateSP(bodySP);
			UpdateBoxSP(bodySP);
		}
	}
	if (currentLayer == 1) {
		UpdateSP(bodySP);//sera o sprite dele subindo a escada
	}
	auto centerPosition = box.GetCenter();
	actualSP.Render(box.GetWorldPosition(), 0, movedLeft);

	Vec2 renderPosition;
	renderPosition.X = centerPosition.X - cannonSp.GetWidth() / 2 - Camera::pos.X;
	renderPosition.Y = centerPosition.Y - cannonSp.GetHeight() / 2 - Camera::pos.Y;

	//cannonSp.Render(renderPosition,cannonAngle); SERA O BRACO
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
	return type == "Player";
}

void Player::UpdateSP(Sprite newSprite) {
	
	if (box.W < newSprite.GetWidth()) {
		UpdateBoxSP(newSprite);
	} else {
		box.W = newSprite.GetWidth();
		box.H = newSprite.GetHeight();
		actualSP = newSprite;
	}
	
}
void Player::UpdateBoxSP(Sprite newSprite) {
	Rect newBox = box;
	newBox.W = newSprite.GetWidth();
	auto collisionAnalysisLayer0 = TileCollision::isCollinding(newBox, 0);
		
	if (collisionAnalysisLayer0 != TileCollision::Solid) {
 		box.W = newSprite.GetWidth();
		box.H = newSprite.GetHeight();
		actualSP = newSprite;
	}
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

void Player::Move(float dt){
	Rect previousRect = box;
	Rect stairsAnalisys= previousRect;
	     stairsAnalisys.Y += speedStairs.Y*dt;
	if (currentLayer == 0) {//Tratamento de acoes caso o player esteja no layer 0
		//EIXO X
		box.X += speed.X*dt;//caso nao tenha colisao,aplicado a movimentacao normal em X
		auto collisionAnalysisX = TileCollision::isCollinding(this->box, currentLayer);
		if (collisionAnalysisX == TileCollision::Solid && currentLayer == 0) {
			box.X = previousRect.X;
		}

		//EIXO Y
		auto collisionAnalysisLayer1 = TileCollision::isCollinding(stairsAnalisys, 1);
		if (collisionAnalysisLayer1 == TileCollision::Stairs && (InputManager::GetInstance().IsKeyDown(SDLK_w) || InputManager::GetInstance().IsKeyDown(SDLK_s))) {
			jumpCount = 0;
			currentLayer = 1;
			CenterOnCurrentTile();
			return;
		}
		
		box.Y += speed.Y*dt;//caso nao tenha colisao,aplicado a movimentacao normal em Y
		auto collisionAnalysisY = TileCollision::isCollinding(this->box,0);
		if (collisionAnalysisY == TileCollision::Solid) {
			speed.Y = 0;
			if (box.Y - previousRect.Y > 0) {
				jumpCount = 0;
			}
			box.Y = previousRect.Y;
			return;
		}
	}

	if (currentLayer == 1) {//Tratamento de acoes caso o player esteja no layer 1
		box.Y += speedStairs.Y*dt;
		auto collisionAnalysisLayer1 = TileCollision::isCollinding(this->box, 1);
		auto collisionAnalysisLayer0 = TileCollision::isCollinding(this->box, 0);
		if ( InputManager::GetInstance().KeyPress(SDLK_SPACE) && collisionAnalysisLayer0 != TileCollision::Solid) {
			currentLayer = 0;
			return;
		}

		if (collisionAnalysisLayer1 == TileCollision::noCollision && collisionAnalysisLayer0 != TileCollision::Solid) {
			currentLayer = 0;
			return;
		}
		if (collisionAnalysisLayer1 == TileCollision::Solid) {
			currentLayer = 0;
			box.Y = previousRect.Y;
			return;

		}
	}
}

void Player::CenterOnCurrentTile() {
	auto tileWidth = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileWidth();
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	auto center = box.GetCenter();
	int x = (int)center.X;

	int initialTileX = x - (x % tileWidth);
	int midTileX = initialTileX + (tileWidth / 2 - 1);

	box.SetCenter((float)midTileX, center.Y);
}
