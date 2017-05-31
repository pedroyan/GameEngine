#pragma once
#include "GameObject.h"
#include "Text.h"
class Portal : public GameObject {
	public:
		Portal(string text, Rect dimensions);
		void Update(float dt);
		void Render();
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);
		~Portal();

	private:
		Text portalText;
		bool renderText;
};

