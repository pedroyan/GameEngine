#include "GameObject.h"
#include "Camera.h"
#include "Debug.h"



void GameObject::CreateDebugBox(Vec2 position) {
	Debug::MakeDebugSquare(position.X, position.Y,box.W, box.H, 0, 0, 255);
	Debug::MakeDebugSquare(position.X, position.Y, box.W, box.H/2, 0, 0, 255);
	Debug::MakeDebugSquare(position.X, position.Y, box.W/2, box.H, 0, 0, 255);
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

