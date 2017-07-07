#pragma once
#include "GameObject.h"
#include "Text.h"
#include "Timer.h"
#include "Sprite.h"
class Portal : public GameObject {
	public:
		Portal(string nextMap, string nextTileSet, Rect dimensions ,string text = "Pressione F para a Proxima Fase");
		void Update(float dt);
		void Render();
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);
		~Portal();

	private:
		Text displayText;
		Sprite sp;
		Timer teleportTime;

		string text;
		string nextMap;
		string nextTileSet;

		bool OpenRequested;

		void CenterDisplayText();
		void UpdateText(string text);
};

