#pragma once
#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Camera.h"
#include "Music.h"

class TitleState : public State{
	public:
		TitleState();
		~TitleState();

		void Update(float dt);
		void Render();

		void Pause();
		void Resume();

	private:
		Sprite bg1;
		Sprite bg2;
		Text mainText;
		Timer textTimer;
		Music  menuMusic;
};

