#include "Resources.h"
#include "Game.h"
#include "Logger.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;

shared_ptr<SDL_Texture> Resources::GetImage(string file) {
	auto iterator = imageTable.find(file);

	if (iterator == imageTable.end()) {
		Game& gameInstance = Game::GetInstance();
		SDL_Texture* texture = IMG_LoadTexture(gameInstance.GetRenderer(), file.c_str());

		if (texture == nullptr) {
			string error = SDL_GetError();
			Logger::LogError(error);
			exit(0);
		}
		auto deleteCallback = [](SDL_Texture* texture) {
			SDL_DestroyTexture(texture);
		};

		shared_ptr<SDL_Texture> shared(texture,deleteCallback);
		imageTable.emplace(std::make_pair(file, shared));
		return shared;
	} else {
		return iterator->second;
	}
}

shared_ptr<Mix_Music> Resources::GetMusic(string file) {
	auto iterator = musicTable.find(file);

	if (iterator == musicTable.end()) {
		auto music = Mix_LoadMUS(file.c_str());

		if (music == nullptr) {
			Logger::LogError(SDL_GetError());
			exit(0);
		}

		auto deleteCallback = [](Mix_Music* musicptr) {
			Mix_FreeMusic(musicptr);
		};
		shared_ptr<Mix_Music> shared(music, deleteCallback);
		return shared;
	} else {
		return iterator->second;
	}
}

void Resources::ClearImages() {
	for (auto it = imageTable.begin(); it != imageTable.end();) {
		if ((*it).second.unique()) {
			it = imageTable.erase(it);
		} else {
			it++;
		}
	}
}

void Resources::ClearMusic() {
	for (auto it = musicTable.begin(); it != musicTable.end();) {
		if ((*it).second.unique()) {
			it = musicTable.erase(it);
		} else {
			it++;
		}
	}
}
