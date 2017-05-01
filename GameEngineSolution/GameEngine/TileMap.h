#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "TileSet.h"
#include "RapidXML\rapidxml.hpp"

using std::string;
using std::stringstream;
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
		/// Pega as dimens�es especificadas no n�
		/// </summary>
		/// <param name="node">N� do XML analisado</param>
		/// <param name="width">Vari�vel onde ser� inserida a largura especificada no n�</param>
		/// <param name="height">Vari�vel onde ser� inserida a altura especificada no n�</param>
		void GetDimensionProperties(xml_node<>* node, int * width, int * height);

		/// <summary>
		/// Confere a validade da layer e insere os tiles na matriz
		/// </summary>
		/// <param name="layerNode">Layer a ser analisada</param>
		/// <returns>Ponteiro para proxima layer. Null caso n�o exista proxima layer</returns>
		xml_node<>* parseLayer(xml_node<>* layerNode);

		/// <summary>
		/// Seta a matriz de tiles
		/// </summary>
		/// <param name="stream">string stream contendo as informa��es no formato CSV das posi��es dos tiles</param>
		void setTileMatrix(stringstream &stream);

		void readTileIndex(stringstream &stream, char buffer[]);

		/// <summary>
		/// Carrega o arquivo XML para a mem�ria.
		/// </summary>
		/// <param name="fileName">Nome do arquivo a ser carregado</param>
		/// <returns>string contendo o XML carregado</returns>
		char* loadTMXtoMemory(string fileName);

};

