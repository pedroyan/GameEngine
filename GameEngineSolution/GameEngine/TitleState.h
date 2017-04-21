#pragma once
#include "State.h"
#include "Sprite.h"
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
};

