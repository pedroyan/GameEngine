#pragma once
class State {
	public:
		State();
		~State();
		bool QuitRequested();
		void Update();
		void Render();
	private:
		//Sprite bg;
		bool quitRequested;
};

