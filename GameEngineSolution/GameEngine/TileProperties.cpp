#include "TileProperties.h"

bool TileProperties::GetIsSolid(){
	return isSolid;
}

void TileProperties::SetIsSolid(bool isSolid){
	this->isSolid = isSolid;
}

bool TileProperties::GetIsSnow()
{
	return isSnow;
}

void TileProperties::SetIsSnow(bool isSnow){
	this->isSnow = isSnow;
}
