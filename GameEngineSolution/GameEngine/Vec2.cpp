#include "Vec2.h"
#include <math.h>


Vec2::Vec2() {
	X = 0;
	Y = 0;
}

float Vec2::Magnitude() {
	return (float)sqrt(X*X + Y*Y);
}

Vec2 Vec2::Normalize() {
	float norm = Magnitude();
	return (*this) / norm;
}

float Vec2::GetDistance(Vec2 destinyPoint) {
	Vec2 diferenceVector = (*this) - destinyPoint;
	return diferenceVector.Magnitude();
}

float Vec2::GetDistanceVectorAngle(Vec2 destinyPoint) {
	Vec2 distanceVector = destinyPoint - (*this);
	return distanceVector.GetXAxisAngle();
}

float Vec2::GetXAxisAngle() {
	return (float)atan2(Y, X);
}

void Vec2::Rotate(float angulo) {

	float previousX = X;

	X = previousX * cos(angulo) - Y * sin(angulo);
	Y = Y * cos(angulo) + previousX * sin(angulo);
}

Vec2::Vec2(float x, float y) {
	X = x;
	Y = y;
}

bool Vec2::Equals(Vec2 vector) {
	return vector.X == X && vector.Y == Y;
}

Vec2 Vec2::operator+(const Vec2 soma) {
	Vec2 result;
	result.X = X + soma.X;
	result.Y = Y + soma.Y;
	return result;
}

Vec2 Vec2::operator-(const Vec2 subtracao) {
	Vec2 result;
	result.X = X - subtracao.X;
	result.Y = Y - subtracao.Y;
	return result;
}

Vec2 Vec2::operator*(const float escalar) const{
	Vec2 result;
	result.X = X*escalar;
	result.Y = Y*escalar;
	return result;
}

Vec2 Vec2::operator/(const float escalar) {
	Vec2 result;
	result.X = X / escalar;
	result.Y = Y / escalar;
	return result;
}

Vec2 & Vec2::operator+=(const Vec2 rhs) {
	this->X += rhs.X;
	this->Y += rhs.Y;
	return *this;
}


Vec2::~Vec2() {
}
