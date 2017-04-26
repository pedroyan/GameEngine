#pragma once
#include <string>
#include <SDL_mixer.h>
#include <memory>
using std::string;

class Sound {
	public:
	Sound();
	Sound(string file);
	~Sound();

	void Play(int times);
	void Stop();
	void Open(string file);
	bool IsOpen();

	private:
	std::shared_ptr<Mix_Chunk> chunk;
	int channel;
};

