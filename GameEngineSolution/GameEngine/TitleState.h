#pragma once
#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State{
	public:
		TitleState();
		~TitleState();

		void Update(float dt);
		void Render();

		void Pause();
		void Resume();

	private:
		Sprite bg;
		Text mainText;
		Timer textTimer;
};

