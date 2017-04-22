#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <memory>

using std::unordered_map;
using std::string;
using std::shared_ptr;

class Resources {
	public:
		static shared_ptr<SDL_Texture> GetImage(string file);
		static shared_ptr<Mix_Music> GetMusic(string file);
		static void ClearImages();
		static void ClearMusic();
	private:
		static unordered_map<string,shared_ptr<SDL_Texture>> imageTable;
		static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
};

