#include "Resources.h"
#include "Game.h"
#include "Logger.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;

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
		musicTable.emplace(std::make_pair(file, shared));
		return shared;
	} else {
		return iterator->second;
	}
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file) {
	auto iterator = soundTable.find(file);

	if (iterator == soundTable.end()) {
		Mix_Chunk* sound = Mix_LoadWAV(file.c_str());

		if (sound == nullptr) {
			Logger::LogError(SDL_GetError());
			exit(0);
		}

		auto deleteCallback = [](Mix_Chunk* chunckPtr) {
			Mix_FreeChunk(chunckPtr);
		};

		shared_ptr<Mix_Chunk> shared(sound, deleteCallback);
		soundTable.emplace(std::make_pair(file, shared));
		return shared;
	} else {
		return iterator->second;
	}
}

shared_ptr<TTF_Font> Resources::GetFont(string fontName,int fontSize) {
	string uniqueKey = fontName + std::to_string(fontSize);
	auto iterator = fontTable.find(uniqueKey);

	if (iterator == fontTable.end()) {

		TTF_Font* font = TTF_OpenFont(fontName.c_str(),fontSize);

		if (font == nullptr) {
			Logger::LogError(SDL_GetError());
			exit(0);
		}

		auto deleteCallback = [](TTF_Font* myFont) {
			TTF_CloseFont(myFont);
		};

		shared_ptr<TTF_Font> shared(font, deleteCallback);
		fontTable.emplace(std::make_pair(uniqueKey, shared));
		return shared;
	} else {
		return iterator->second;
	}
}

void Resources::ClearImages() {
	genericClear<SDL_Texture>(imageTable);
}

void Resources::ClearMusic() {
	genericClear<Mix_Music>(musicTable);
}

void Resources::ClearSound() {
	genericClear<Mix_Chunk>(soundTable);
}

void Resources::ClearFont() {
	genericClear<TTF_Font>(fontTable);
}
