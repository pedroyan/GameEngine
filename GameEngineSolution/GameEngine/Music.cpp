#include "Music.h"
#include "Resources.h"

Music::Music() {
	music = nullptr;
}

Music::Music(string file) {
	Open(file);
}

void Music::Play(int times) {
	Mix_PlayMusic(music.get(), times);
}

void Music::Stop() {
	Mix_FadeOutMusic(0);
}

void Music::Open(string file) {
	music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
	return music != nullptr;
}

