#pragma once
#include <unordered_map>
#include <SDL_image.h>

using std::unordered_map;
using std::string;

class Resources {
	public:
		static SDL_Texture* GetImage(string file);
		static void ClearImages();
	private:
		static unordered_map<string, SDL_Texture*> imageTable;
};

