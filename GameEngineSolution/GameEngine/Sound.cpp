#include "Sound.h"
#include "Resources.h"


Sound::Sound() {
	chunk = nullptr;
}

Sound::Sound(string file) {
	Open(file);
}


Sound::~Sound() {

}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk.get(), times);
	Mix_Playing(channel);
}

void Sound::Stop() {
	Mix_HaltChannel(channel);
}

void Sound::Open(string file) {
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
	return chunk != nullptr;
}
