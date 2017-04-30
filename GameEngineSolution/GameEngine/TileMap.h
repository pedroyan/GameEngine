#pragma once
#include <string>
#include <vector>
#include "TileSet.h"
#include "RapidXML\rapidxml.hpp"

using std::string;
using namespace rapidxml;

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
		/// Seta as dimensões do tileMap a partir do nó map
		/// </summary>
		/// <param name="mapNode">xml node chamado map</param>
		void SetDimensionsFromMap(xml_node<>* mapNode);

		void setTileMatrix(FILE* fp);

		/// <summary>
		/// Carrega o arquivo XML para a memória.
		/// </summary>
		/// <param name="fileName">Nome do arquivo a ser carregado</param>
		/// <returns>string contendo o XML carregado</returns>
		char* loadTMXtoMemory(string fileName);

};

