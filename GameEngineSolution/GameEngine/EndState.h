#pragma once
#include "StateData.h"
#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Music.h"

class EndState : public State {
	public:
		EndState(StateData stateData);
		~EndState();

		void Update(float dt);
		void Render();

		void Pause();
		void Resume();

	private:
		Text instruction;
		Sprite bg;
		Music music;
		
};

