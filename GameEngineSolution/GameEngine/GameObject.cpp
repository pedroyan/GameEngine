#include "GameObject.h"
#include "Camera.h"



GameObject::GameObject() {
	rotation = 0;
}

GameObject::~GameObject()
{
	if (Camera::IsBeeingFollowed(this)) {
		Camera::Unfollow();
	}
}

