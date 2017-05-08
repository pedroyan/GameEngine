#include "TileProperties.h"

bool TileProperties::GetIsWall(){
	return isWall;
}

void TileProperties::SetIsWall(bool iswall){
	this->isWall = iswall;
}

bool TileProperties::GetIsFloor()
{
	return isFloor;
}

void TileProperties::SetIsFloor(bool isFloor){
	this->isFloor = isFloor;
}
