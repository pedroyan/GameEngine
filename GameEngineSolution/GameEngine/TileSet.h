#pragma once
#include <string>
#include "Sprite.h"

using std::string;
class TileSet {
	public:
		TileSet(int Width, int Height, string file);
		~TileSet();

		/// <summary>
		/// Renderiza o tile escolhido por um indice na posição indicada
		/// por x e y
		/// </summary>
		/// <param name="index">Indice do tile a ser renderizado</param>
		/// <param name="x">Posição	X do ponto de renderização</param>
		/// <param name="y">Posição Y do ponto de renderização</param>
		void Render(unsigned int index, float x, float y);

	private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
};

