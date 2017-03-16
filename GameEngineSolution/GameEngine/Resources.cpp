#include "Resources.h"
#include "Game.h"
#include "Logger.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;

SDL_Texture * Resources::GetImage(string file) {
	auto iterator = imageTable.find(file);

	if (iterator == imageTable.end()) {
		Game* gameInstance = Game::GetInstance();
		SDL_Texture* texture = IMG_LoadTexture(gameInstance->GetRenderer(), file.c_str());

		if (texture == nullptr) {
			string error = SDL_GetError();
			Logger::LogError(error);
			exit(0);
		}

		imageTable.emplace(std::make_pair(file, texture));
		return texture;
	} else {
		return iterator->second;
	}
}

void Resources::ClearImages() {
	for (auto& x : imageTable) {
		SDL_DestroyTexture(x.second);
	}
}
