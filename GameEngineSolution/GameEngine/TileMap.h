#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Rect.h"
#include "TileSet.h"
#include "RapidXML\rapidxml.hpp"
#include "XMLParser.h"

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
		TileMap(XMLParser& parser, TileSet* tilesetVariable);

		void Load(XMLParser& parser);

		void SetTileSet(TileSet*  tileSetVariable);

		int* At(int x, int y, int z = 0);
		
		void Render(int cameraX = 0, int cameraY = 0, int layerInitial=0, int layerFinal= -1);

		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

		int GetWidth();
		int GetPlayerLayer();
		int GetHeight();
		int GetDepth();
		std::vector<Vec2> GetSpawnTiles();
		TileSet* GetTileSet();

		~TileMap();
	private:
	/// <summary>
	/// Obtem os tiles que podem spawnar criaturas
	/// </summary>
	/// <param name="deltaY">Distancia minima do tileSolid em relacao a outro tileSolid</param>
	/// <param name="layer">Layer na qual sera feita essa analise</param>
	void ObtainSpawnTile( int layer);
		std::vector<Vec2> spawnTiles;
		std::vector<int> tileMatrix;
		TileSet* tileSet;

		int spaceSpawn = 3;
		int mapWidth;
		int mapHeight;
		int mapDepth;
		int playerLayer;

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
};

