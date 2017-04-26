#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <memory>
#include <SDL_ttf.h>

using std::unordered_map;
using std::string;
using std::shared_ptr;

class Resources {
	public:
		static shared_ptr<SDL_Texture> GetImage(string file);
		static shared_ptr<Mix_Music> GetMusic(string file);
		static shared_ptr<Mix_Chunk> GetSound(string file);

		/// <summary>
		/// Aloca a fonte com o tamanho passado
		/// </summary>
		/// <param name="fontPath">Caminho para fonte</param>
		/// <param name="size">Tamanho da ponte</param>
		/// <returns></returns>
		static shared_ptr<TTF_Font> GetFont(string fontPath, int size);

		static void ClearImages();
		static void ClearMusic();
		static void ClearSound();
		static void ClearFont();
	private:
		static unordered_map<string,shared_ptr<SDL_Texture>> imageTable;
		static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
		static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
		static unordered_map<string, shared_ptr<TTF_Font>> fontTable;

		template<class T>
		static void genericClear(unordered_map<string, shared_ptr<T>>& table);
};

template<class T>
inline void Resources::genericClear(unordered_map<string, shared_ptr<T>>& table) {
	for (auto it = table.begin(); it != table.end();) {
		if ((*it).second.unique()) {
			it = table.erase(it);
		} else {
			it++;
		}
	}
}
