#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include <memory>

using std::unordered_map;
using std::string;
using std::shared_ptr;

class Resources {
	public:
		static shared_ptr<SDL_Texture> GetImage(string file);
		static void ClearImages();
	private:
		static unordered_map<string,shared_ptr<SDL_Texture>> imageTable;
};

