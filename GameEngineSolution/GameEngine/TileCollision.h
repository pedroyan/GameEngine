#pragma once
#include "Rect.h"
#include "TileMap.h"
#include <vector>
#include "CollisionTypeh.h"

using std::vector;
class TileCollision{
public:

	/// <summary>
	/// Analisa se a box esta colidindo com algo
	/// </summary>
	/// <param name="box">Box(codernadas x,y e tamanhos w,h) do objeto a qual ira ser analisado</param>
	/// <param name="layer">Layer na qual ira ser analisada a colisao</param>
	/// <returns>Tipo de colisao que o player esta sofrendo de maior prioridade</returns>
	static CollisionType PriorityCollision(Rect box,int layer);

	/// <summary>
	///  Analisa quais tiles a box colide
	/// </summary>
	/// <param name="box">Box(codernadas x,y e tamanhos w,h) do objeto a qual ira ser analisado</param>
	/// <param name="layer">Layer na qual ira ser analisada a colisao</param>
	/// <returns>Quais colisões foram encontradas</returns>
	static vector<CollisionType> GetCollisions(Rect box, int layer);

	/// <summary>
	/// Analisa se a box está colidindo com o tipo passado
	/// </summary>
	/// <param name="box">Box(codernadas x,y e tamanhos w,h) do objeto a qual ira ser analisado</param>
	/// <param name="layer">Layer na qual ira ser analisada a colisao</param>
	/// <param name="type">Tipo que está sendo verificado</param>
	/// <returns>Um boleano indicando se a box está colidindo com o tipo passado</returns>
	static bool HasCollision(Rect box, int layer, CollisionType type);

	/// <summary>
	/// Obtem os parametros do mapa
	/// </summary>
	/// <param name="mapa">mapa a qual sera analisada a colisao</param>
	static void GetParameters(TileMap mapa);
	
private:
	static TileMap map;
	static int tile_height;
	static int tile_width;
	static int map_height;
	static int map_width;
};
