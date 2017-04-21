#pragma once
#include <string>
#include <SDL_mixer.h>
using std::string;

class Music {
	public:
	Music();
	Music(string file);
	
	void Play(int times);
	void Stop();
	void Open(string file);
	bool IsOpen();

	private:
	Mix_Music* music;
};

