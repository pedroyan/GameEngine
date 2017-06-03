#include "GameObject.h"
#include "Camera.h"
#include "Debug.h"



void GameObject::CreateDebugBox() {
	Debug::MakeCenteredDebugSquare(box, { 250, 244, 29 });
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

