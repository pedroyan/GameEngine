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
#include "Raio.h"

Player* Player::playerInstance = nullptr;

const float jumpHeight = 2; // em blocos
const float Gravity = 2 * 9.8;

//cooldown de tiro em segundos
const float coolDown = 0.1;
const float chargingTimeLimit = 1.0;

Player::Player(float x, float y) : bodySP("img/MainPlayer.png"), bodyRunSP("img/MainPlayerRun.png", 6, 0.1), jumpSP("img/jumpPlayer.png",4,0.1,true), armSP("img/armPlayer.png"), stairsSP("img/stairsPlayer.png",2,0.2), playerLife("img/Life.png")
{
	rotation = 0;
	Player::playerInstance = this;
	fullHp = 10000;//vida aumentada pra teste
	hp = fullHp;//vida aumentada pra teste
	cooldownCounter = Timer();

	box.X = x;
	box.Y = y;
	box.W = bodySP.GetWidth();
	box.H = bodySP.GetHeight();
	SpeedLimit = 400; 

	jumpCount = 0;
	keyCount = 0;

	playerLife.SetScaleX(0.1);
	playerLife.SetScaleY(0.1);
}

Player::~Player() {
	Player::playerInstance = nullptr;
}

void Player::Update(float dt) {
	auto& input = InputManager::GetInstance();
	UpdateAllSprites(dt,input);
	
	if (cooldownCounter.Get() != 0) {
		cooldownCounter.Update(dt);
		if (cooldownCounter.Get() > 0) {
			cooldownCounter.Restart();
		}
	}
	if (input.KeyPress(SDLK_l)) {
		Camera::ZoomTo(1.0f, 5);
	} else if (input.KeyPress(SDLK_k)) {
		Camera::ZoomTo(0.5, 3);
	}
	MovePlayer(dt, input);
	UpdateCannonAngle(input);
}

void Player::Render() {
	playerLife.Render(10, 10);

	auto& input = InputManager::GetInstance();
	Vec2 renderPosition;
	auto centerPosition = box.GetCenter();
	renderPosition.X = centerPosition.X - concertaX - concertaLeft - Camera::pos.X;
	renderPosition.Y = centerPosition.Y - concertaY - Camera::pos.Y;

	if (CurrentLayer == 0) {
		if (isJumping) {
			UpdateSP(jumpSP);
			UpdateConcertaArm(35, 28, -5);
			if (actualSP.GetCurrentFrame() == actualSP.GetFrameCount()-1) {
				armSP.Render(renderPosition, cannonAngle, false, Camera::Zoom);
			}

		}
		else if (input.IsKeyDown(SDLK_d) || input.IsKeyDown(SDLK_a)) {
			UpdateSP(bodyRunSP);
			UpdateConcertaArm(20,26,20);
		//	Sound("audio/passos.wav").Play(0);
			armSP.Render(renderPosition, cannonAngle, false, Camera::Zoom);
		} else {
			UpdateSP(bodySP);
			UpdateConcertaArm(35, 28,5);
			armSP.Render(renderPosition, cannonAngle, false, Camera::Zoom);
			
		}
		actualSP.Render(box.GetWorldRenderPosition(), 0, movedLeft, Camera::Zoom);
	
		
	}
	if (CurrentLayer == 1) {
		UpdateSP(stairsSP);
	
		actualSP.Render(box.GetWorldRenderPosition(), 0, movedLeft, Camera::Zoom);
	}
	

	
}
void Player::UpdateConcertaArm(int correcaoX, int correcaoY,int correcaoLeft) {
	concertaX = correcaoX;
	concertaY = correcaoY;
	concertaLeft = 0;
	if (movedLeft) {
		concertaLeft = correcaoLeft;
	}
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

void Player::UpdateAllSprites(float dt, InputManager& input) {
	bodyRunSP.Update(dt);
	jumpSP.Update(dt);
	if(input.IsKeyDown(SDLK_w) || input.IsKeyDown(SDLK_s)) {
		stairsSP.Update(dt);
	}
	
}


void Player::Shoot() {
	Vec2 cannonOffset(50, 0);
	cannonOffset.Rotate(cannonAngle);
	
	Sprite bulletSprite;
	
	if (chargeCounter.Get() > chargingTimeLimit) {
		bulletSprite = Sprite("img/tiroCarregadoPlayer.png", 3,0.3,true);
		Sound("audio/LazerCarregado.wav").Play(0);
		auto pos = bulletSprite.GetCentralizedRenderPoint(box.GetCenter()) + cannonOffset + Vec2(0,-20);
		auto bullet = new Bullet(pos.X, pos.Y, cannonAngle, getInertialBulletSpeed(), 1000, bulletSprite, false,100);
		chargeCounter.Restart();
		Game::GetInstance().GetCurrentState().AddObject(bullet);
	} else {
		bulletSprite = Sprite("img/tiroPlayer.png", 2,0.1);
		Sound("audio/LazerSimples.wav").Play(0);
		auto pos = bulletSprite.GetCentralizedRenderPoint(box.GetCenter()) + cannonOffset + Vec2(0, -20);
		auto bullet = new Bullet(pos.X, pos.Y, cannonAngle, getInertialBulletSpeed(), 1000, bulletSprite, false, 10);
		chargeCounter.Restart();
		Game::GetInstance().GetCurrentState().AddObject(bullet);
		cooldownCounter.Update(-coolDown);
	}
}

void Player::Bolt() {
	Vec2 finalOffSet;
	Vec2 cannonOffset(210,-30);
	finalOffSet = cannonOffset;
	if (abs(cannonAngle) >1.5) {
		Vec2 cannonOffset2(200,15);
		finalOffSet = cannonOffset2;
	}
	finalOffSet.Rotate(cannonAngle);

	Sprite bulletSprite;

		bulletSprite = Sprite("img/raio.png", 6, 0.08);
		Sound("audio/LazerCarregado.wav").Play(0);
		auto pos = bulletSprite.GetCentralizedRenderPoint(box.GetCenter()) + finalOffSet;
		auto raio = new Raio(pos.X, pos.Y, cannonAngle, getInertialBulletSpeed()*2, 500, bulletSprite, false, 5);
		chargeCounter.Restart();
		Game::GetInstance().GetCurrentState().AddObject(raio);
	
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

float Player::getInertialBoltSpeed() {
	Vec2 bulletSpeed(500, 0);
	bulletSpeed.Rotate(cannonAngle);
	return (bulletSpeed + Speed).Magnitude();
}

void Player::TakeDamage(int damage) {
	hp -= damage;
	double percent = (double) hp / fullHp;
	playerLife.SetScaleX(1);
	playerLife.SetScaleY(1);
	playerLife.SetClip(10, 10, (int)playerLife.GetWidth()*percent, playerLife.GetHeight());
	playerLife.SetScaleX(0.1);
	playerLife.SetScaleY(0.1);

	if (IsDead()) {
		Game::GetInstance().GetCurrentState().AddObject(new Animation(box.GetWorldRenderPosition(), rotation, "img/morteEnemy70.png", 5, 0.125, true));
		Sound("audio/enemyDeath.wav").Play(0);
	}
}

void Player::MovePlayer(float dt, InputManager& input){

	//Primeira faz o calculo da velocidade resultante final
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	if (CurrentLayer == 0) {//caso o player NÃO esteja na escada
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
			jumpSP.SetCurrentFrame(0);
			Sound("audio/pulo.wav").Play(0);
			
		} else {
			ApplyGravity(dt);
		}
		if (input.MouseRelease(LEFT_MOUSE_BUTTON) && cooldownCounter.Get() == 0) {
			Shoot();
		}
		if (input.KeyPress(SDLK_r)) {
			Bolt();
		}
	} 
	else if (CurrentLayer == 1) {//caso o player esteja na layer de escada
		UpdateSpeedStairs(input);
		QuitStairs = input.KeyPress(SDLK_SPACE) || input.KeyPress(SDLK_d) || input.KeyPress(SDLK_a);
		if (input.KeyPress(SDLK_SPACE) && jumpCount <2) {
			jumpPlayer();
		}
	}

	//Depois movimenta o objeto
	auto collisionResult = MoveOnSpeed(dt);

	//E finalmente trata as colisões
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
