#pragma once
#include "Rect.h"
class GameObject
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;

	Rect box;

	virtual ~GameObject();
};

