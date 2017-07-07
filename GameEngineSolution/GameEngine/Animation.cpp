#include "Animation.h"
#include "Camera.h"

Animation::Animation(Vec2 center, float rotationv, string sprite, int framecount ,float frameTime, bool ends) :sp(sprite,framecount,frameTime) {

	box.W = sp.GetWidth();
	box.H = sp.GetHeight();
	box.SetCenter(center);

	rotation = rotationv;
	timeLimit = framecount*frameTime;
	oneTimeOnly = ends;
	endTimer = Timer();
}

void Animation::Update(float dt) {
	sp.Update(dt);
	endTimer.Update(dt);
}

void Animation::Render() {
	sp.Render(box.GetWorldRenderPosition(),0,false,Camera::Zoom);
}

bool Animation::IsDead() {
	return oneTimeOnly && endTimer.Get() >= timeLimit;
}

void Animation::NotifyCollision(GameObject & other) {
}

bool Animation::Is(string type) {
	return type == "Animation";
}

Animation::~Animation() {
}
