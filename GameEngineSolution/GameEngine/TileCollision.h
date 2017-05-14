#pragma once
#include "Rect.h"
#include "TileMap.h"
class TileCollision{
public:

	enum CollisionType {//quanto maior o enum,maior a prioridade da colissao
		noCollision = 0,
		Snow,
		Solid
	}type;
	/// <summary>
	/// Analisa se o player esta colidindo com algo
	/// </summary>
	/// <param name="box">Box(codernadas x,y e tamanhos w,h) do objeto a qual ira ser analisado</param>
	/// <returns>Tipo de colisao que o player esta sofrendo de maior prioridade</returns>
	static CollisionType isCollinding(Rect box);
	static void GetParameters(TileMap mapa);
	
private:
	static TileMap map;
	static int tile_height;
	static int tile_width;


};
