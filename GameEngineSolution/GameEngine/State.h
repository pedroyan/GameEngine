#pragma once
#include "Sprite.h"

class State {
	public:
		State();
		~State();
		bool QuitRequested();
		void Update(float dt);
		void Render();
	private:
		Sprite bg;
		bool quitRequested;
};

