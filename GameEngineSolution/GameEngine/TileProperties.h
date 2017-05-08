#pragma once
class	TileProperties {
public:
	bool GetIsWall();
	void SetIsWall(bool iswall);
	bool GetIsFloor();
	void SetIsFloor(bool isFloor);
private:
	bool isWall=false;
	bool isFloor = false;
};