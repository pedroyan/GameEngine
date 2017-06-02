#pragma once
#include "GameObject.h"
#include "Text.h"
class Portal : public GameObject {
	public:
		Portal(string nextMap, string nextTileSet, Rect dimensions,int nextPlayerLayer, string text = "Pressione F para a Proxima Fase");
		void Update(float dt);
		void Render();
		bool IsDead();
		void NotifyCollision(GameObject& other);
		bool Is(string type);
		~Portal();

	private:
		Text portalText;
		string nextMap;
		string nextTileSet;
		int nextPlayerLayer;
};

