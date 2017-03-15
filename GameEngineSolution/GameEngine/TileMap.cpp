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
				tileMatrix.insert(tileMatrix.end(), tileIndex);

			}
			//ignora o \n
			c = fgetc(fp);
		}
		//ignora o \n
		c = fgetc(fp);
	}
}

