#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include <SDL.h>

//static Vec2 pos;
//static Vec2 speed;
//static GameObject* focus;

Vec2 Camera::speed(1000, 1000);
Vec2 Camera::pos;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject * newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if (focus == nullptr) {
		UpdateOnInput(dt);
	} else {
		UpdateOnFocus();
	}
}

bool Camera::IsBeeingFollowed(GameObject * followed) {
	return followed == focus;
}

void Camera::UpdateOnInput(float dt) {
	Vec2 direction;
	auto& input = InputManager::GetInstance();

	direction.X = input.IsKeyDown(LEFT_ARROW_KEY) ? -1 : 0;
	direction.X = input.IsKeyDown(RIGHT_ARROW_KEY) ? direction.X + 1 : direction.X;

	direction.Y = input.IsKeyDown(UP_ARROW_KEY) ? - 1 : 0;
	direction.Y = input.IsKeyDown(DOWN_ARROW_KEY) ? direction.Y + 1 : direction.Y;

	Vec2 deslocamento = speed*dt;
	deslocamento.X = deslocamento.X*direction.X;
	deslocamento.Y = deslocamento.Y*direction.Y;
	pos = pos + deslocamento;
}

void Camera::UpdateOnFocus() {
	float gameWidth = DEFAULT_GAME_WIDTH;
	float gameHeight = DEFAULT_GAME_HEIGHT;

	Vec2 center = focus->box.GetCenter();

	pos.X = center.X - gameWidth / 2.0;
	pos.Y = center.Y - gameHeight / 2.0;
}
