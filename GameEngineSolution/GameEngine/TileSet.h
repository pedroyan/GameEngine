#pragma once
#include <string>
#include "Sprite.h"

using std::string;
class TileSet {
	public:
		TileSet(int Width, int Height, string file);
		~TileSet();

		/// <summary>
		/// Renderiza o tile escolhido por um indice na posi��o indicada
		/// por x e y
		/// </summary>
		/// <param name="index">Indice do tile a ser renderizado</param>
		/// <param name="x">Posi��o	X do ponto de renderiza��o</param>
		/// <param name="y">Posi��o Y do ponto de renderiza��o</param>
		void Render(unsigned int index, float x, float y);

	private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
};

