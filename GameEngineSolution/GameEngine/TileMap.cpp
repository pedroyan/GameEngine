#include "TileMap.h"
#include <stdio.h>


TileMap::~TileMap() {
	delete tileSet;
}

TileMap::TileMap(string file, TileSet * tileSetVariable) {
	Load(file);
	tileSet = tileSetVariable;
}

void TileMap::Load(string file) {
	FILE* fp = fopen(file.c_str(),"r");
	if (fp == NULL) {
		printf("Erro ao abrir arquivo %s\n", file);
		return;
	}

	SetDimensionsFromFile(fp);
	setTileMatrix(fp);
}

/// <summary>
/// Seta as dimensões do mapa a partir FilePointer
/// recém aberto
/// </summary>
/// <param name="fp">Ponteiro para o arquivo aberto</param>
void TileMap::SetDimensionsFromFile(FILE * fp) {
	char dimensionString[9];

	fgets(dimensionString, 9, fp);
	sscanf(dimensionString, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);
}

void TileMap::SetTileSet(TileSet * set) {
	tileSet = set;
}

void TileMap::setTileMatrix(FILE * fp) {
	char c = fgetc(fp); // pega o primeiro \n
	c = fgetc(fp); //pega o segundo \n

	for (size_t i = 0; i < mapDepth; i++) {
		for (size_t j = 0; j < mapHeight; j++) {
			for (size_t k = 0; k < mapWidth; k++) {
				int tileIndex;

				char tileString[4];
				fgets(tileString, 4, fp);
				sscanf(tileString, "%d,", &tileIndex);

				//subtrai o numero lido por 1 para adequar aos padrões do projeto
				tileIndex -= 1;
				tileMatrix.insert(tileMatrix.end(), tileIndex);

			}
			//ignora o \n
			c = fgetc(fp);
		}
		//ignora o \n
		c = fgetc(fp);
	}
}

int * TileMap::At(int x, int y, int z) {
	unsigned int unsigX = x;
	unsigned int unsigY = y;
	unsigned int unsigZ = z;

	if (unsigX >= mapWidth || unsigY >= mapHeight || unsigZ >= mapDepth) {
		throw std::out_of_range("Dimensões passadas são maiores do que as do mapa");
	}

	unsigned int heigthOffset = unsigY*mapWidth;
	unsigned int depthOffset = unsigZ*mapHeight*mapWidth;

	unsigned int index = unsigX + heigthOffset + depthOffset;

	return &tileMatrix[index];
}

void TileMap::Render(int cameraX, int cameraY) {
	for (size_t i = 0; i < mapDepth; i++) {
		RenderLayer(i, cameraX, cameraY);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	unsigned int unsigLayer = layer;

	if (unsigLayer >= mapDepth) {
		throw std::out_of_range("Layer fora de alcance");
	}

	int layerSize = mapHeight*mapWidth;

	int startIndex = unsigLayer*layerSize;

	for (size_t i = 0; i < mapHeight; i++) {
		for (size_t j = 0; j < mapWidth; j++) {
			int index = i*mapWidth + j + startIndex;
			tileSet->Render(tileMatrix[index], tileSet->GetTileWidth()*j, tileSet->GetTileHeight()*i);
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

