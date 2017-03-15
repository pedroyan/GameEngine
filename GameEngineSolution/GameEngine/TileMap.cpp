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
}

/// <summary>
/// Seta as dimensões do mapa a partir FilePointer
/// recém aberto
/// </summary>
/// <param name="fp">Ponteiro para o arquivo aberto</param>
void TileMap::SetDimensionsFromFile(FILE * fp) {
	char dimensionString[8];

	fgets(dimensionString, 8, fp);
	sscanf(dimensionString, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);
}

