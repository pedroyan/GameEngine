#include "TileMap.h"
#include "RapidXML\rapidxml_print.hpp"
#include <fstream>
#include <stdio.h>

using std::ifstream;
using std::getline;



TileMap::~TileMap() {
}

TileMap::TileMap(){
}

TileMap::TileMap(string file, TileSet * tileSetVariable) {
	mapDepth = 0;
	tileSet = tileSetVariable;
	Load(file);
	
}

void TileMap::Load(string fileName) {

	char* input_TMX = loadTMXtoMemory(fileName);
	xml_document<> doc;
	doc.parse<0>(input_TMX);

	auto mapNode = doc.first_node("map", 0U, true);
	GetDimensionProperties(mapNode,&mapWidth,&mapHeight);
	xml_node<>* TileSetNode = mapNode->first_node("tileset");
	auto tilesNode = TileSetNode->first_node("tile");
	
	while (tilesNode != nullptr) {
		tilesNode =GetTilesProperties(tilesNode);
	}
	xml_node<>* layerNode = mapNode->first_node("layer");

	while (layerNode != nullptr) {
		layerNode = parseLayer(layerNode);
		mapDepth++;
	}

	free(input_TMX);
}

/// <summary>
/// Seta as dimens�es do tileMap a partir do n� map
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
/// <returns>Ponteiro para proxima layer. Null caso n�o exista proxima layer</returns>
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
		printf("Codificacao %s n�o suportada pela engine.", encodingType.c_str());
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
/// <param name="stream">string stream contendo as informa��es no formato CSV das posi��es dos tiles</param>
void TileMap::setTileMatrix(stringstream &stream) {
	int tileIndex;
	char tileString[10];

	stream.read(tileString, 1);
	for (int j = 0; j < mapHeight; j++) {
		for (int k = 0; k < mapWidth; k++) {

			readTileIndex(stream, tileString);
			sscanf(tileString, "%d,", &tileIndex);

			//subtrai o numero lido por 1 para adequar aos padr�es do projeto
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
/// Carrega o arquivo TMX para a mem�ria. Lan�a exce��o caso o arquivo n�o consiga ser carregado
/// </summary>
/// <param name="filename">Nome do arquivo a ser carregado</param>
/// <returns>string contendo o TMX carregado</returns>
char* TileMap::loadTMXtoMemory(string fileName) {
	ifstream file(fileName);

	if (!file.is_open()) {
		printf("Nao foi possivel abrir o arquivo %s", fileName.c_str());
		throw new std::exception();
		exit(0);
	}

	string line;
	string input_TMX;
	while (getline(file, line))
		input_TMX += line + "\n";

	char* chr = _strdup(input_TMX.c_str());
	return chr;
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
		propertiesNode = AddPropertie(propertiesNode,indexNode);
	}

	return tileNode->next_sibling();
}

xml_node<>* TileMap::AddPropertie(xml_node<>* propertiesNode, int indexNode){
	bool Bollean;
	string propertieType = propertiesNode->first_attribute("name")->value();

	if (propertieType == "Solid") {
		string propertiesNodeSolid = propertiesNode->first_attribute("value")->value();
		int isSolidInt = 0;
		sscanf(propertiesNodeSolid.c_str(), "%d", &isSolidInt);
		if (isSolidInt == 1) {
			Bollean = true;
		} else {
			Bollean = false;
		}
		this->tileSet->AddTileSolidPropertie(indexNode, Bollean);
	}
	if (propertieType == "Snow") {
		string propertiesNodeSolid = propertiesNode->first_attribute("value")->value();
		int isSolidInt = 0;
		sscanf(propertiesNodeSolid.c_str(), "%d", &isSolidInt);
		if (isSolidInt == 1) {
			Bollean = true;
		} else {
			Bollean = false;
		}
		this->tileSet->AddTileSnowPropertie(indexNode, Bollean);
	}
	
	return propertiesNode->next_sibling();
}

int * TileMap::At(int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0) {
		throw std::exception(); // n�o � poss�vel passar valores menores que 0
	}

	if (x >= mapWidth || y >= mapHeight || z >= mapDepth) {
		throw std::exception(); // n�o � possivel utilizar valores fora do indice
	}

	int heigthOffset = y*mapWidth;
	int depthOffset = z*mapHeight*mapWidth;

	int index = x + heigthOffset + depthOffset;

	return &tileMatrix[index];
}

void TileMap::Render(int cameraX, int cameraY) {
	for (int i = 0; i < mapDepth; i++) {
		RenderLayer(i, cameraX, cameraY);
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

}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

TileSet * TileMap::GetTileSet(){
	return tileSet;
}

