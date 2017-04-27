#include "TileMap.h"
#include <stdio.h>


TileMap::~TileMap() {
}

TileMap::TileMap(string file, TileSet * tileSetVariable) {
	Load(file);
	tileSet = tileSetVariable;
}

void TileMap::Load(string file) {
	FILE* fp = fopen(file.c_str(),"r");
	if (fp == NULL) {
		printf("Erro ao abrir arquivo %s\n", file.c_str());
		return;
	}

	SetDimensionsFromFile(fp);
	setTileMatrix(fp);
	fclose(fp);
}

/// <summary>
/// Seta as dimens�es do mapa a partir FilePointer
/// rec�m aberto
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
	fgetc(fp); // pega o primeiro \n
	fgetc(fp); //pega o segundo \n

	for (int i = 0; i < mapDepth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			for (int k = 0; k < mapWidth; k++) {
				int tileIndex;

				char tileString[4];
				fgets(tileString, 4, fp);
				sscanf(tileString, "%d,", &tileIndex);

				//subtrai o numero lido por 1 para adequar aos padr�es do projeto
				tileIndex -= 1;
				tileMatrix.insert(tileMatrix.end(), tileIndex);

			}
			//ignora o \n
			fgetc(fp);
		}
		//ignora o \n
		fgetc(fp);
	}
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

