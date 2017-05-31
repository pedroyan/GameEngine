#pragma once
#include "Rect.h"

class TileMap;

//flag
enum class collisionDirection {
	Left = 1,
	Top=2,
	Right=4,
	Bottom=8
};

//menor numero = maior prioridade
enum class CollisionType {
	noCollision = 0,
	Stairs,
	Solid
};

struct CollisionDTO {
	unsigned char directionFlags;
	CollisionType type;
};

class TileCollision{
public:

	/// <summary>
	/// Analisa se a box passada está colidindo com um tile
	/// </summary>
	/// <param name="box">Box(codernadas x,y e tamanhos w,h) do objeto a qual ira ser analisado</param>
	/// <param name="layer">Layer na qual ira ser analisada a colisao</param>
	/// <returns>Tipo de colisao que o player esta sofrendo de maior prioridade</returns>
	static CollisionType isColliding(Rect box,int layer);

	/// <summary>
	/// Analise se o ponto passado esta colidindo com um tile
	/// </summary>
	/// <param name="point">ponto passado</param>
	/// <param name="layer">Layer na qual ira ser analisada a colisao</param>
	/// <returns></returns>
	static CollisionType isColliding(Vec2 point, int layer);

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
