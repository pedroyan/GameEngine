#pragma once
class	TileProperties {
public:
	bool GetIsSolid();
	void SetIsSolid(bool isSolid);
	bool GetIsSnow();
	void SetIsSnow(bool isSnow);
private:
	bool isSolid=false;
	bool isSnow = false;
};