#include "Enemy.h"
#include "Debug.h"
#include "PriorityQueue.h"
#include "TileCollision.h"
#include "Pathfinding.h"
#include "Game.h"
#include "Sound.h"
#include "Animation.h"
#include "Raio.h"
#include "Bullet.h"
#include "RangedEnemy.h"

const float jumpHeight = 11;
const float Gravity = 2 * 9.8;
const float sqrK1 = sqrt(2 * Gravity * jumpHeight);

Enemy::~Enemy() {
}

void Enemy::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box, { 250, 0, 0 });
}

void Enemy::MoveTo(Vec2 pos, float dt) {
	PriorityQueue<Vec2, double> frontier;
	Vec2 newPos;
	auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
	auto neig = FindNeighbors(200 * dt, tileHeight * sqrK1 * dt, pos);
	bool walked = false;

	if (!neig.empty()) {
		for (auto next : neig) {
			frontier.put(next, heuristic(pos, next));
		}

		while (!frontier.empty()) {
			newPos = frontier.get();
			Rect newPosBox = box;
			newPosBox.X = newPos.X;
			newPosBox.Y = newPos.Y;
			auto collisionAnalysis = TileCollision::PriorityCollision(newPosBox, 0);

			if (collisionAnalysis == CollisionType::Solid) {
				continue;
			}

			if (collisionAnalysis == CollisionType::noCollision) {
				if (newPos.Y - box.Y > 20) { //esta mais alto
					if (!isJumping && ground) { //posso pular?
						walked = true;
						ground = false;
						if (box.X > newPos.X) {
							Speed.X = -200;
							walkingLeft = true;
						} else {
							Speed.X = 200;
							walkingLeft = false;
						}
						Jump(2);
						break;
					}
					else {
						continue;
					}
				} else if(fabs(pos.Y - box.Y) < 10) {
					walked = true;
					if (box.X > newPos.X) {
						Speed.X = -200;
						walkingLeft = true;
					} else {
						Speed.X = 200;
						walkingLeft = false;
					}
					break;
				}
			}
		}
	}

	if (!walked) {//não andei
		if (fabs(pos.Y - box.Y) < 10) {//parede entre a gente
			Rect newPosBox = box;
			newPosBox.X = box.X + 200 * dt;
			newPosBox.Y = box.Y + tileHeight * sqrK1;
			auto collisionAnalysisR = TileCollision::PriorityCollision(newPosBox, 0);

			newPosBox.X = box.X - 200 * dt;
			newPosBox.Y = box.Y + tileHeight * sqrK1;
			auto collisionAnalysisL = TileCollision::PriorityCollision(newPosBox, 0);
			if (collisionAnalysisL == CollisionType::noCollision || collisionAnalysisR == CollisionType::noCollision) {//se eu pular eu contorno
				if (!isJumping && ground) { //posso pular?
					walked = true;
					ground = false;
					Jump(2);
					if (box.X > newPos.X) {
						Speed.X = -200;
						walkingLeft = true;
					}
					else {
						Speed.X = 200;
						walkingLeft = false;
					}
				}
			}
		} else if(box.Y - pos.Y > 10) {//escada de tiles entre a gente
			if (!isJumping && ground) { //posso pular?
				walked = true;
				ground = false;
				Jump(2);
				if (box.X > newPos.X) {
					Speed.X = -200;
					walkingLeft = true;
				}
				else {
					Speed.X = 200;
					walkingLeft = false;
				}
			}
		}
	}

	if (!walked && fabs(pos.X - box.X) < 1) {
		walked = true;
		GoToStairs = true;
	}
}

void Enemy::EnemyMove(float dt) {
	if (CurrentLayer == 0) {
		auto tileHeight = Game::GetInstance().GetCurrentState().GetMap().GetTileSet()->GetTileHeight();
		Speed.Y += tileHeight * Gravity * dt;
		box.Y += Speed.Y*dt;

	

		auto collisionAnalysisY = TileCollision::PriorityCollision(this->box, 0);
		if (collisionAnalysisY == CollisionType::Solid) {
			box.Y -= Speed.Y*dt;
			Speed.Y = 0;
		}
	}
	else if (CurrentLayer == 1) {
		box.Y += Speed.Y*dt;
		auto collisionAnalysisLayer1 = TileCollision::PriorityCollision(this->box, 1);
		auto collisionAnalysisLayer0 = TileCollision::PriorityCollision(this->box, 0);

		if (collisionAnalysisLayer1 == CollisionType::noCollision && collisionAnalysisLayer0 != CollisionType::Solid) {
			CurrentLayer = 0;
			GoToStairs = false;
		}
		if (collisionAnalysisLayer1 == CollisionType::Solid) {
			if (Speed.Y > 0) {
				CurrentLayer = 0;
				GoToStairs = false;
			}
			box.Y -= Speed.Y*dt;
		}
	}
}

void Enemy::Focus(Player* focus) {
	this->focus = focus;
}

Enemy::Enemy(Sprite stillSprite, Sprite walkingSprite,Sprite stairsSprite) : stillSprite(stillSprite), walkingSprite(walkingSprite), stairsSprite(stairsSprite){
	focus = nullptr;
	actualSprite = &this->stillSprite;
}

void Enemy::MoveToDumbly(Vec2 pos) {
	//pathfinding tosco e menos custoso
}

std::list<Vec2> Enemy::FindNeighbors(float tileWidth, float tileHeight, Vec2 pos) {
	list<Vec2> neighbors;
	if (pos.X > box.X) {
	
		
	//		walkingLeft = false;
		
		
		neighbors.push_back(Vec2(box.X + tileWidth, box.Y));
		neighbors.push_back(Vec2(box.X + tileWidth, box.Y - tileHeight));
	} else if (pos.X < box.X) {

		

		neighbors.push_back(Vec2(box.X - tileWidth, box.Y));
		neighbors.push_back(Vec2(box.X - tileWidth, box.Y - tileHeight));
	}
	
	return neighbors;
}


void Enemy::DummyWalk(float dt) {
	if (walked >= 0 && walked <= 40) {
		walked++;
		Speed.X = 100;
		walkingLeft = false;
	} else if (walked <= 0 && walked >= -40) {
		walked--;
		Speed.X = -100;
		walkingLeft = true;
	} else if (walked > 0) {
		walked = -1;
	} else if (walked < 0) {
		walked = 1;
	}
}

void Enemy::NotifyCollision(GameObject & other) {
	if (other.Is("Bullet") && !static_cast<const Bullet&>(other).targetsPlayer) {
		hp -= other.damage;
	}

	if (other.Is("Bolt") && !static_cast<const Raio&>(other).targetsPlayer) {
		hp -= other.damage;
	}

	if (IsDead()) {
		Vec2 animation;
		animation.X = box.X;
		animation.Y = box.Y;
		Game::GetInstance().GetCurrentState().AddObject(new Animation(animation, rotation, "img/morteEnemy70.png", 5, 0.125, true));
		Sound("audio/enemyDeath.wav").Play(0);
	}
}
