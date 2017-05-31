#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Rect.h"
#include "TileSet.h"
#include "RapidXML\rapidxml.hpp"

using std::string;
using std::stringstream;
using std::unordered_map;
using namespace rapidxml;

/// <summary>
/// Simula uma matriz tridimensional que representa o mapa e suas diversas camadas
/// </summary>
class TileMap {
	public:
		TileMap();
		TileMap(string file, TileSet* tileSetVariable);

		void Load(string fileName);

		void SetTileSet(TileSet*  tileSetVariable);

		int* At(int x, int y, int z = 0);

		void Render(int cameraX = 0, int cameraY = 0);

		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

		int GetWidth();
		int GetHeight();
		int GetDepth();
		TileSet* GetTileSet();

		~TileMap();
	private:
		std::vector<int> tileMatrix;
		TileSet* tileSet;

		int mapWidth;
		int mapHeight;
		int mapDepth;

		/// <summary>
		/// Pega as dimensões especificadas no nó
		/// </summary>
		/// <param name="node">Nó do XML analisado</param>
		/// <param name="width">Variável onde será inserida a largura especificada no nó</param>
		/// <param name="height">Variável onde será inserida a altura especificada no nó</param>
		void GetDimensionProperties(xml_node<>* node, int * width, int * height);

		/// <summary>
		/// Confere a validade da layer e insere os tiles na matriz
		/// </summary>
		/// <param name="layerNode">Layer a ser analisada</param>
		/// <returns>Ponteiro para proxima layer. Null caso não exista proxima layer</returns>
		xml_node<>* parseLayer(xml_node<>* layerNode);

		xml_node<>* parseObjectLayer(xml_node<>* objLayer);

		/// <summary>
		/// Seta a matriz de tiles
		/// </summary>
		/// <param name="stream">string stream contendo as informações no formato CSV das posições dos tiles</param>
		void setTileMatrix(stringstream &stream);

		void readTileIndex(stringstream &stream, char buffer[]);

		/// <summary>
		/// Carrega as propiedades dos tiles
		/// </summary>
		/// <param name="tileNode">Nome do no a ser lido</param>
		/// <returns>Proximo no a ser lido</returns>
		xml_node<>* GetTilesProperties(xml_node<>* node);

		/// <summary>
		/// Adiciona uma propiedade ao tile.
		/// </summary>
		/// <param name="tileNode">Tile que esta sendo lido</param>
		/// <param name="indexNode">Index do tile que esta sendo lido</param>
		/// <returns></returns>
		xml_node<>* AddProperty(xml_node<>* tileNode, int indexNode);

		/// <summary>
		/// Extrai as propriedades do objeto
		/// </summary>
		/// <param name="objectNode">Nó xml do objeto</param>
		/// <returns>propriedades do objeto extraidas</returns>
		unordered_map<string, string> GetObjectProperties(xml_node<>* objectNode);

		void CreateMapObject(string type, Rect dimensions, unordered_map<string, string> properties);
};

