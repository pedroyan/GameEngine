#include "Resources.h"
#include "Game.h"
#include "Logger.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;

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

void Resources::ClearImages() {
	for (auto it = imageTable.begin(); it != imageTable.end();) {
		if ((*it).second.unique()) {
			it = imageTable.erase(it);
		} else {
			it++;
		}
	}
}
