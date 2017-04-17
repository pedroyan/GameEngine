#include "Animation.h"

Animation::Animation(float x, float y, float rotationv, Sprite sprite, float timeLimitV, bool ends) {
	sp = sprite;

	box.X = x;
	box.Y = y;
	box.W = sp.GetWidth();
	box.H = sp.GetHeight();

	rotation = rotationv;
	timeLimit = timeLimitV;
	oneTimeOnly = ends;
	endTimer = Timer();
}

void Animation::Update(float dt) {
	sp.Update(dt);
	endTimer.Update(dt);
}

void Animation::Render() {
	sp.Render(box.GetWorldPosition(), rotation);
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
