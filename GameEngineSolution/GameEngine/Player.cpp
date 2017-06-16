#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"
#include <math.h>
#include "StageState.h"
#include "TileCollision.h"
#include "Item.h"
#include "Debug.h"

Player* Player::playerInstance = nullptr;

const float jumpHeight = 2; // em blocos
const float Gravity = 2 * 9.8;

//cooldown de tiro em segundos
const float coolDown = 0.5;
const float chargingTimeLimit = 1.0;

Player::Player(float x, float y) : bodySP("img/MainPlayer.png"), bodyRunSP("img/MainPlayerRun.png", 6, 0.1), cannonSp("img/cubngun.png"){
	rotation = 0;
	Player::playerInstance = this;
	hp = 100;
	cooldownCounter = Timer();

	box.X = x;
	box.Y = y;
	box.W = bodySP.GetWidth();
	box.H = bodySP.GetHeight();
	SpeedLimit = 400; 

	jumpCount = 0;
	keyCount = 0;
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
	if (input.KeyPress(SDLK_l)) {
		Camera::ZoomTo(1.0f, 5);
	}
	MovePlayer(dt, input);
	UpdateCannonAngle(input);
}

void Player::Render() {
	auto& input = InputManager::GetInstance();
	if (CurrentLayer == 0) {
		if (input.IsKeyDown(SDLK_d) || input.IsKeyDown(SDLK_a)) {
			UpdateSP(bodyRunSP);		
		} else {
			UpdateSP(bodySP);
		}
	}
	if (CurrentLayer == 1) {
		UpdateSP(bodySP);
	}
	actualSP.Render(box.GetWorldRenderPosition(), 0, movedLeft, Camera::Zoom);
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
		TakeDamage(other.damage);
	}

	if (other.Is("Item")) {
		auto item = static_cast<const Item&>(other);
		auto type = item.GetType();
		switch (type) {
			case ItemType::Key:
				keyCount++;
				break;
			default:
				break;
		}
	}
}

bool Player::Is(string type) {
	return type == "Player";
}

void Player::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box, { 0, 244, 0 });
}

int Player::GetKeyCount() const {
	return keyCount;
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
		bulletSprite = Sprite("img/tiroPlayer.png", 4,0.1);
		auto pos = bulletSprite.GetCentralizedRenderPoint(box.GetCenter()) + cannonOffset;
		auto bullet = new Bullet(pos.X, pos.Y, cannonAngle, getInertialBulletSpeed(), 1000, bulletSprite, false, 10);
		chargeCounter.Restart();
		Game::GetInstance().GetCurrentState().AddObject(bullet);
		cooldownCounter.Update(-coolDown);
	}
}


void Player::UpdateCannonAngle(InputManager & manager) {
	Vec2 mousePosition(manager.GetWorldMouseX(), manager.GetWorldMouseY());

#ifdef _DEBUG
	Rect mouseRect;
	mouseRect.W = 50;
	mouseRect.H = 50;
	mouseRect.SetCenter(mousePosition);
	Debug::MakeCenteredDebugSquare(mouseRect, { 255,255,255 });
#endif // _DEBUG

	Vec2 cannonAxis = box.GetCenter();

	cannonAngle = cannonAxis.GetDistanceVectorAngle(mousePosition);
}

float Player::getInertialBulletSpeed() {
	Vec2 bulletSpeed(1000, 0);
	bulletSpeed.Rotate(cannonAngle);
	return (bulletSpeed + Speed).Magnitude();
}

void Player::TakeDamage(int damage) {
	hp -= damage;
	if (IsDead()) {
		Game::GetInstance().GetCurrentState().AddObject(new Animation(box.GetCenter(), rotation, "img/penguindeath.png", 5, 0.125, true));
		Sound("audio/boom.wav").Play(0);
	}
}

void Player::MovePlayer(float dt, InputManager& input){

	//Primeira faz o calculo da velocidade resultante final
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	if (CurrentLayer == 0) {//caso o player N�O esteja na esada
		if (input.IsMouseDown(LEFT_MOUSE_BUTTON)) {
			chargeCounter.Update(dt);
		}
		if (input.IsKeyDown(SDLK_d)) {
			Speed.X = SpeedLimit;
			movedLeft = false;
		} else if (input.IsKeyDown(SDLK_a)) {
			Speed.X = -SpeedLimit;
			movedLeft = true;
		} else {
			Speed.X = 0;
		}

		GoToStairs = input.IsKeyDown(SDLK_w) || input.IsKeyDown(SDLK_s);
		if (input.KeyPress(SDLK_SPACE) && jumpCount <2) {
			jumpPlayer();
		} else {
			Speed.Y += tileHeight * Gravity*dt;
		}
		if (input.MouseRelease(LEFT_MOUSE_BUTTON) && cooldownCounter.Get() == 0) {
			Shoot();
		}
	} 
	else if (CurrentLayer == 1) {//caso o player esteja na layer de escada
		UpdateSpeedStairs(input);
		QuitStairs = input.KeyPress(SDLK_SPACE);
		if (input.KeyPress(SDLK_SPACE) && jumpCount <2) {
			jumpPlayer();
		}
	}

	//Depois movimenta o objeto
	auto collisionResult = Move(dt);

	//E finalmente trata as colis�es
	if (collisionResult & (int)CollisionFlags::Bottom) {
		jumpCount = 0;
	}

}

void Player::jumpPlayer() {
	Jump(jumpHeight);
	jumpCount++;
}

void Player::UpdateSpeedStairs(InputManager& input) {
	if (input.IsKeyDown(SDLK_w)) {
		Speed.Y = -SpeedLimit / 2;
	} else if (input.IsKeyDown(SDLK_s)) {
		Speed.Y = +SpeedLimit / 2;
	} else {
		Speed.Y = 0;
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
