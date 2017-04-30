#pragma once
#include <string>
#include <vector>
#include "TileSet.h"

using std::string;

/// <summary>
/// Simula uma matriz tridimensional que representa o mapa e suas diversas camadas
/// </summary>
class TileMap {
	public:
		TileMap(string file, TileSet* tileSetVariable);

		void Load(string fileName);

		void SetTileSet(TileSet*  tileSetVariable);

		int* At(int x, int y, int z = 0);

		void Render(int cameraX = 0, int cameraY = 0);

		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

		int GetWidth();
		int GetHeight();
		int GetDepth();

		~TileMap();
	private:
		std::vector<int> tileMatrix;
		TileSet* tileSet;

		int mapWidth;
		int mapHeight;
		int mapDepth;

		/// <summary>
		/// Seta as dimensões do mapa a partir FilePointer
		/// recém aberto
		/// </summary>
		/// <param name="fp">Ponteiro para o arquivo aberto</param>
		void SetDimensionsFromFile(FILE* fp);

		void setTileMatrix(FILE* fp);

		/// <summary>
		/// Carrega o arquivo XML para a memória.
		/// </summary>
		/// <param name="fileName">Nome do arquivo a ser carregado</param>
		/// <returns>string contendo o XML carregado</returns>
		string loadTMXtoMemory(string fileName);


};

