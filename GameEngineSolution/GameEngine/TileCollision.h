#pragma once
#include "Rect.h"
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
	


};
