#pragma once
#include <string>
#include "Sprite.h"
#include "TileProperties.h"
#include <unordered_map>

using std::unordered_map;

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

		int GetTileWidth();

		int GetTileHeight();
		/// <summary>
		/// Descobre se o tile analisado � uma wall(colide com objetos) 
		/// </summary>
		/// <param name="tileSet">tile analisado</param>
		/// <returns>true para wall e false para background</returns>
		bool isWall(int tileSet);
		/// <summary>
		/// Adiciona ao tile a propriedades ao um tile
		/// </summary>
		/// <param name="tileIndex">tile a ser adicionado a nova popriedade</param>
		/// <param name="isWall">bool para ser uma Wall(colide com objetos)</param>
		void AddTileWallPropertie(int tileIndex, bool isWall);
		void AddTileFloorPropertie(int tileIndex, bool isWall);

	private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
	    unordered_map<int,TileProperties> tilesProperties;
};

