#include "GameObject.h"
#include "Camera.h"
#include "Debug.h"



void GameObject::CreateDebugBox() {
	auto pos = box.GetWorldPosition();
	Debug::MakeDebugSquare(pos.X, pos.Y,box.W, box.H, 255, 0, 0);
	Debug::MakeDebugSquare(pos.X, pos.Y, box.W, box.H/2, 255, 0, 0);
	Debug::MakeDebugSquare(pos.X, pos.Y, box.W/2, box.H, 255, 0, 0);
}

bool GameObject::IsEnemy() {
	return false;
}

GameObject::GameObject() {
	rotation = 0;
}

GameObject::~GameObject()
{
	if (Camera::IsBeeingFollowed(this)) {
		Camera::Unfollow();
	}
}

