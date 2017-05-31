#pragma once
#include <string>
#include "Sprite.h"
#include <unordered_map>
#include "TileCollision.h"

using std::unordered_map;

using std::string;
class TileSet {
	public:

		TileSet(int Width, int Height, string file);
		~TileSet();

		/// <summary>
		/// Renderiza o tile escolhido por um indice na posição indicada
		/// por x e y
		/// </summary>
		/// <param name="index">Index do tile a ser renderizado</param>
		/// <param name="x">Posição	X do ponto de renderização</param>
		/// <param name="y">Posição Y do ponto de renderização</param>
		void Render(unsigned int index, float x, float y);

		int GetTileWidth();

		int GetTileHeight();
		/// <summary>
		/// Descobre a propriedade do tile
		/// </summary>
		/// <param name="tileIndex">tile a ser analisado</param>
		/// <returns>a propriedade que o tile possui</returns>
		CollisionType GetTileProperty(int tileIndex);

		/// <summary>
		/// Adiciona uma propriedade ao tile,
		/// </summary>
		/// <param name="tileIndex">index do tile que ganhara a proriedade</param>
		/// <param name="tileType">propriedade do tile</param>
		void AddTileProperty(int tileIndex,CollisionType tileType);

	private:
		
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
	    unordered_map<int,CollisionType> tilesProperties;
};

