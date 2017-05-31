#include "Portal.h"


Portal::Portal(string text, Rect dimensions) : portalText("adam-cg-pro.regular.otf",12,Text::TextStyle::BLENDED, text, { 255,255,255,255 }){
	box = dimensions;
}

void Portal::Update(float dt) {
}

void Portal::Render() {
	if (renderText) {
		portalText.Render();
	}
}

bool Portal::IsDead() {
	return false;
}

void Portal::NotifyCollision(GameObject & other) {
	if (other.Is("Player")) {
		renderText = true;
	}
}

bool Portal::Is(string type) {
	return type == "Portal";
}


Portal::~Portal() {
}
