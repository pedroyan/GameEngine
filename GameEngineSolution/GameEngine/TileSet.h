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
		/// Renderiza o tile escolhido por um indice na posição indicada
		/// por x e y
		/// </summary>
		/// <param name="index">Indice do tile a ser renderizado</param>
		/// <param name="x">Posição	X do ponto de renderização</param>
		/// <param name="y">Posição Y do ponto de renderização</param>
		void Render(unsigned int index, float x, float y);

		int GetTileWidth();

		int GetTileHeight();
		/// <summary>
		/// Descobre se o tile analisado é uma Solid(colide com objetos) 
		/// </summary>
		/// <param name="tileSet">tile analisado</param>
		/// <returns>true para Solid e false para outro tipo</returns>
		bool isSolid(int tileSet);
		/// <summary>
		/// Analise se o tile eh to tipo Snow
		/// </summary>
		/// <param name="tileSet">tile analisado</param>
		/// <returns>true para Snow e false outro tipo</returns>
		bool isSnow(int tileSet);
		/// <summary>
		/// Adiciona ao tile a propriedades ao um tile
		/// </summary>
		/// <param name="tileIndex">tile a ser adicionado a nova propriedade</param>
		/// <param name="isSolid">bool para ser uma Solid(colide com objetos)</param>
		void AddTileSolidPropertie(int tileIndex, bool isSolid);
		/// <summary>
		/// Adiciona ao tile a propriedade Snow
		/// </summary>
		/// <param name="tileIndex">tile a ser adicionado a nova propriedade</param>
		/// <param name="isSolid">bool para ser um Sbow(abaixa a velocidade)</param>
		void AddTileSnowPropertie(int tileIndex, bool isSolid);

	private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
	    unordered_map<int,TileProperties> tilesProperties;
};

