#include "Rect.h"



Rect Rect::operator+(const Vec2 vec) {
	Rect result;

	result.X = X + vec.X;
	result.Y = Y + vec.Y;
	result.W = W;
	result.H = H;

	return result;
}

Vec2 Rect::GetCenter() {
	Vec2 toReturn;

	toReturn.X = X + W / 2;
	toReturn.Y = Y + H / 2;

	return toReturn;
}

float Rect::DistanceFrom(Rect otherRectangle) {
	Vec2 centerFromThis = GetCenter();
	Vec2 centerFromOther = otherRectangle.GetCenter();

	return centerFromThis.GetDistance(centerFromOther);
}

bool Rect::IsInside(Vec2 coordinates) {
	return coordinates.X >= X && coordinates.X <= X + W
		&& coordinates.Y >= Y && coordinates.Y <= Y + H;
}

Rect::Rect() {
	X = 0;
	Y = 0;
	W = 0;
	H = 0;
}

Rect::Rect(int x, int y, int w, int h) {
	X = x;
	Y = y;
	W = w;
	H = h;
}


Rect::~Rect() {
}
