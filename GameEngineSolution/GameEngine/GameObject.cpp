#include "GameObject.h"
#include "Camera.h"


GameObject::~GameObject()
{
	if (Camera::IsBeeingFollowed(this)) {
		Camera::Unfollow();
	}
}
