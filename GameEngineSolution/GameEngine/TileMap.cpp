#include "TileMap.h"
#include "RapidXML\rapidxml_print.hpp"
#include <fstream>
#include <stdio.h>
#include "Logger.h"
#include "Portal.h"
#include "StringLibrary.h"
#include "Game.h"
#include "TileCollision.h"
#include "Debug.h"

using std::ifstream;
using std::getline;

TileMap::~TileMap() {
}

TileMap::TileMap(){
}

TileMap::TileMap(string file, TileSet * tileSetVariable) {
	mapDepth = 0;
	tileSet = tileSetVariable;
	XMLParser parser(file);
	Load(parser);
	ObtainSpawnTile(0);
	
}

TileMap::TileMap(XMLParser & parser, TileSet * tilesetVariable) {
	mapDepth = 0;
	tileSet = tilesetVariable;
	Load(parser);
	ObtainSpawnTile(0);
}

void TileMap::Load(XMLParser & parser) {

	auto mapNode = parser.GetMapNode();
	GetDimensionProperties(mapNode,&mapWidth,&mapHeight);
	
	auto propertiesNode = mapNode->first_node("properties")->first_node("property");
	if (propertiesNode != nullptr) {
		string propertyeType = propertiesNode->first_attribute("name")->value();
		if (propertyeType == "playerLayer") {
			string playerLayerString = propertiesNode->first_attribute("value")->value();
			sscanf(playerLayerString.c_str(), "%d", &this->playerLayer);
		}

	}
	xml_node<>* TileSetNode = mapNode->first_node("tileset");
	auto tilesNode = TileSetNode->first_node("tile");
	
	while (tilesNode != nullptr) {
		tilesNode =GetTilesProperties(tilesNode);
	}
	xml_node<>* Node = mapNode->first_node();

	while (Node != nullptr) {
		string NodeName(Node->name());
		if (NodeName == "layer") {
			Node = parseLayer(Node);
			mapDepth++;
		} else {
			Node = Node->next_sibling();
		}
		
	}
}

/// <summary>
/// Seta as dimensões do tileMap a partir do nó map
/// </summary>
/// <param name="mapNode">xml node chamado map</param>
void TileMap::GetDimensionProperties(xml_node<>* mapNode, int* width, int* height) {
	string widthS = mapNode->first_attribute("width")->value();
	sscanf(widthS.c_str(), "%d", width);

	string heightS = mapNode->first_attribute("height")->value();
	sscanf(heightS.c_str(), "%d", height);
}

void TileMap::SetTileSet(TileSet * set) {
	tileSet = set;
}

/// <summary>
/// Confere a validade da layer e insere os tiles na matriz
/// </summary>
/// <param name="layerNode">Layer a ser analisada</param>
/// <returns>Ponteiro para proxima layer. Null caso não exista proxima layer</returns>
xml_node<>* TileMap::parseLayer(xml_node<>* layerNode) {

	//Valida tamanho
	int altura;
	int largura;

	GetDimensionProperties(layerNode, &largura, &altura);

	if (largura != mapWidth) {
		printf("Layer invalida: Largura da layer e diferente da largura do mapa");
		throw std::exception();
		exit(0);
	}

	if (altura != mapHeight) {
		printf("Layer invalida: Altura da layer e diferente da altura do mapa");
		throw std::exception();
		exit(0);
	}

	//valida encoding
	auto dataNode = layerNode->first_node("data");
	string encodingType = dataNode->first_attribute("encoding")->value();

	if (encodingType != "csv") {
		printf("Codificacao %s não suportada pela engine.", encodingType.c_str());
		throw std::exception();
		exit(0);
	}

	stringstream ss;
	ss << dataNode->value();
	setTileMatrix(ss);

	return layerNode->next_sibling();
}

/// <summary>
/// Seta a matriz de tiles
/// </summary>
/// <param name="stream">string stream contendo as informações no formato CSV das posições dos tiles</param>
void TileMap::setTileMatrix(stringstream &stream) {
	int tileIndex;
	char tileString[10];

	stream.read(tileString, 1);
	for (int j = 0; j < mapHeight; j++) {
		for (int k = 0; k < mapWidth; k++) {

			readTileIndex(stream, tileString);
			sscanf(tileString, "%d,", &tileIndex);

			//subtrai o numero lido por 1 para adequar aos padrões do projeto
			tileIndex -= 1;
			tileMatrix.insert(tileMatrix.end(), tileIndex);

		}
		//ignora o \n
		stream.read(tileString, 1);
	}

}

/// <summary>
/// Armazena o valor do tile index no buffer
/// </summary>
/// <param name="stream">StringStream a ser parseada</param>
/// <param name="buffer">buffer onde sera armazenado o valor extraido</param>
void TileMap::readTileIndex(stringstream & stream, char buffer[]) {
	int i = 0;
	char temp = ' ';

	while (temp != ',' && temp != '\n') {
		stream.read(&temp, 1);
		buffer[i] = temp;
		i++;
	}

	buffer[i] = '\0';
}

/// <summary>
/// Carrega as propiedades dos tiles
/// </summary>
/// <param name="tileNode">Nome do no a ser lido</param>
/// <returns>Proximo no a ser lido</returns>
xml_node<>* TileMap::GetTilesProperties(xml_node<>* tileNode){
	int indexNode;
	
	
	string indexNodeS = tileNode->first_attribute("id")->value();
	sscanf(indexNodeS.c_str(), "%d", &indexNode);
	auto propertiesNode = tileNode->first_node("properties")->first_node("property");	
	while (propertiesNode != nullptr) {
		propertiesNode = AddProperty(propertiesNode,indexNode);
	}

	return tileNode->next_sibling();
}

xml_node<>* TileMap::AddProperty(xml_node<>* propertiesNode, int indexNode){
	string propertyeType = propertiesNode->first_attribute("name")->value();

	if (propertyeType == "Solid") {
		string propertiesNodeSolid = propertiesNode->first_attribute("value")->value();
		if (propertiesNodeSolid == "true") {
			this->tileSet->AddTileProperty(indexNode, TileSet::Solid);
		}
	}
	if (propertyeType == "Stairs") {
		string propertiesNodeSolid = propertiesNode->first_attribute("value")->value();
		if (propertiesNodeSolid == "true") {
			this->tileSet->AddTileProperty(indexNode, TileSet::Stairs);
		} 
		
	}
	
	return propertiesNode->next_sibling();
}


int * TileMap::At(int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0) {
		throw std::exception(); // não é possível passar valores menores que 0
	}

	if (x >= mapWidth || y >= mapHeight || z >= mapDepth) {
		return nullptr;
	}

	int heigthOffset = y*mapWidth;
	int depthOffset = z*mapHeight*mapWidth;

	int index = x + heigthOffset + depthOffset;

	return &tileMatrix[index];
}

void TileMap::Render(int cameraX, int cameraY,int layerInitial, int layerFinal) {
	if (layerFinal < 0 || layerFinal >mapDepth) {
		layerFinal = mapDepth;
	}
	for (int i = layerInitial; i < layerFinal; i++) {
		RenderLayer(i, cameraX, cameraY);
	}
}

void TileMap::ObtainSpawnTile(int layer) {
	int layerSize = mapHeight*mapWidth;
	int startIndex = layer*layerSize;
	
	for (int j = spaceSpawn; j < mapHeight; j++) {
		for (int i = 0; i < mapWidth; i++) {
			int index = i*mapWidth + j + startIndex;
			int* tile = At(i, j, layer);
			Vec2 coodernadaTile;
			coodernadaTile.X = i;
			coodernadaTile.Y = j-1;
			if (GetTileSet()->GetTileProperty(*tile) == TileCollision::Solid) {
				bool canSpawnEnemy = true;
				for (int z = 1; z <= spaceSpawn; z++) {
					int* tile = At(i, j -z, layer);
					canSpawnEnemy = canSpawnEnemy && (GetTileSet()->GetTileProperty(*tile) == TileCollision::noCollision);
				}
				if (canSpawnEnemy) {
					spawnTiles.push_back(coodernadaTile);
				}
			}
		}
	}

	
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {

	if (layer < 0 || layer >= mapDepth) {
		throw std::exception(); // layer fora de alcance
	}

	int layerSize = mapHeight*mapWidth;

	int startIndex = layer*layerSize;

	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			int index = i*mapWidth + j + startIndex;

			int row = tileSet->GetTileHeight()*i - cameraY;
			int column = tileSet->GetTileWidth()*j - cameraX;

			tileSet->Render(tileMatrix[index],column , row);
		}
	}
	/**********************/
#ifdef _DEBUG
	int spawnTilesSize = this->spawnTiles.size();
		for(int t = 0; t < spawnTilesSize; t++) {
			Debug::MakeDebugSquare(spawnTiles[t].X *tileSet->GetTileHeight() - cameraX, spawnTiles[t].Y * tileSet->GetTileHeight() - cameraY, tileSet->GetTileHeight(), tileSet->GetTileHeight(), 120, 0, 120);
	}
#endif
	/************************/
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetPlayerLayer() {
	return this->playerLayer;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

std::vector<Vec2> TileMap::GetSpawnTiles() {
	return spawnTiles;
}

TileSet * TileMap::GetTileSet(){
	return tileSet;
}

