#include "TileMap.h"
#include "RapidXML\rapidxml_print.hpp"
#include <fstream>
#include <stdio.h>

using std::ifstream;
using std::getline;



TileMap::~TileMap() {
}

TileMap::TileMap(string file, TileSet * tileSetVariable) {
	mapDepth = 0;
	Load(file);
	tileSet = tileSetVariable;
}

void TileMap::Load(string fileName) {

	char* input_TMX = loadTMXtoMemory(fileName);
	xml_document<> doc;
	doc.parse<0>(input_TMX);

	auto mapNode = doc.first_node("map", 0U, true);
	SetDimensionsFromMap(mapNode);

	auto layerNode = mapNode->first_node("layer");
	while (layerNode != nullptr) {
		
	}

	//printf("%s", input_TMX.c_str());

	
	/*SetDimensionsFromFile(fp);
	setTileMatrix(fp);
	fclose(fp);*/

	print(std::back_inserter(s), doc, 0);
	free(input_TMX);
}

/// <summary>
/// Seta as dimensões do tileMap a partir do nó map
/// </summary>
/// <param name="mapNode">xml node chamado map</param>
void TileMap::SetDimensionsFromMap(xml_node<>* mapNode) {
	string widthS = mapNode->first_attribute("width")->value();
	sscanf(widthS.c_str(), "%d", &mapWidth);

	string heightS = mapNode->first_attribute("height")->value();
	sscanf(heightS.c_str(), "%d", &mapHeight);
}

void TileMap::SetTileSet(TileSet * set) {
	tileSet = set;
}

void TileMap::setTileMatrix(FILE * fp) {
		for (int j = 0; j < mapHeight; j++) {
			for (int k = 0; k < mapWidth; k++) {
				int tileIndex;

				char tileString[4];
				fgets(tileString, 4, fp);
				sscanf(tileString, "%d,", &tileIndex);

				//subtrai o numero lido por 1 para adequar aos padrões do projeto
				tileIndex -= 1;
				tileMatrix.insert(tileMatrix.end(), tileIndex);

			}
			//ignora o \n
			fgetc(fp);
		}

}

/// <summary>
/// Carrega o arquivo TMX para a memória. Lança exceção caso o arquivo não consiga ser carregado
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

int * TileMap::At(int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0) {
		throw std::exception(); // não é possível passar valores menores que 0
	}

	if (x >= mapWidth || y >= mapHeight || z >= mapDepth) {
		throw std::exception(); // não é possivel utilizar valores fora do indice
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

