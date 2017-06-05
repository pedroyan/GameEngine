#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"
#include <math.h>
#include "StageState.h"
#include "TileCollision.h"
#include "Debug.h"

Player* Player::playerInstance = nullptr;
//Limite para velocidade adiante
const float SpeedLimit = 400;

const float jumpHeight = 2; // em blocos
const float Gravity = 2 * 9.8;

//cooldown de tiro em segundos
const float coolDown = 0.5;
const float chargingTimeLimit = 1.0;

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
	bodyRunSP.Update(dt);
	if (cooldownCounter.Get() != 0) {
		cooldownCounter.Update(dt);
		if (cooldownCounter.Get() > 0) {
			cooldownCounter.Restart();
		}
	}

	if (input.IsMouseDown(LEFT_MOUSE_BUTTON)) {
		chargeCounter.Update(dt);
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
	
	if (input.KeyPress(SDLK_l)) {
		Camera::ZoomTo(1.3, 5);
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

	Move(dt);
	UpdateCannonAngle(input);

	if (input.MouseRelease(LEFT_MOUSE_BUTTON) && cooldownCounter.Get() == 0) {
		Shoot();
	}
}

void Player::Render() {
	auto& input = InputManager::GetInstance();
	if (currentLayer == 0) {
		if (input.IsKeyDown(SDLK_d) || input.IsKeyDown(SDLK_a)) {
			UpdateSP(bodyRunSP);		
		} else {
			UpdateSP(bodySP);
		}
	}
	if (currentLayer == 1) {
		UpdateSP(bodySP);
	}
	actualSP.Render(box.GetWorldPosition(), 0, movedLeft, Camera::Zoom);
	auto centerPosition = box.GetCenter();

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
		takeDamage(other.damage);
	}
}

bool Player::Is(string type) {
	return type == "Player";
}

void Player::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box, { 0, 244, 0 });
}

void Player::UpdateSP(Sprite newSprite) {
	actualSP = newSprite;
}

void Player::Shoot() {
	Vec2 cannonOffset(50, 0);
	cannonOffset.Rotate(cannonAngle);
	
	Sprite bulletSprite;
	
	if (chargeCounter.Get() > chargingTimeLimit) {
		bulletSprite = Sprite("img/tiroCarregadoPlayer.png", 1);
		auto pos = bulletSprite.GetCentralizedRenderPoint(box.GetCenter()) + cannonOffset;
		auto bullet = new Bullet(pos.X, pos.Y, cannonAngle, getInertialBulletSpeed(), 1000, bulletSprite, false,100);
		chargeCounter.Restart();
		Game::GetInstance().GetCurrentState().AddObject(bullet);
	} else {
		bulletSprite = Sprite("img/tiroPlayer.png", 4);
		auto pos = bulletSprite.GetCentralizedRenderPoint(box.GetCenter()) + cannonOffset;
		auto bullet = new Bullet(pos.X, pos.Y, cannonAngle, getInertialBulletSpeed(), 1000, bulletSprite, false, 10);
		chargeCounter.Restart();
		Game::GetInstance().GetCurrentState().AddObject(bullet);
		cooldownCounter.Update(-coolDown);
	}
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
		 stairsAnalisys.W =0;
		 stairsAnalisys.X += box.W/2;
	if (currentLayer == 0) {//Tratamento de acoes caso o player esteja no layer 0
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
		if (collisionAnalysisY == TileCollision::Solid && currentLayer == 0) {
			speed.Y = 0;
			if (box.Y - previousRect.Y > 0) {
				jumpCount = 0;
			}
			box.Y = previousRect.Y;
			
		}
		//EIXO X
		box.X += speed.X*dt;//caso nao tenha colisao,aplicado a movimentacao normal em X
		auto collisionAnalysisX = TileCollision::isCollinding(this->box, currentLayer);
		if (collisionAnalysisX == TileCollision::Solid && currentLayer == 0) {
			box.X = previousRect.X;
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
			if (speedStairs.Y > 0) {
				currentLayer = 0;
			}
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
