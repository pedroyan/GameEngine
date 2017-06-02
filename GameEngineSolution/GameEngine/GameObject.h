#pragma once
#include "Rect.h"
#include <string>
using std::string;
class GameObject
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject& other) = 0;
	virtual bool Is(string type) = 0;
	/// <summary>
	/// Cria uma debug box em volta do objeto
	/// </summary>
	/// <param name="position">posicao em que o quadrado sera renderizado</param>
	virtual void CreateDebugBox(Vec2 position);

	GameObject();

	Rect box;
	float rotation;
	int damage;

	virtual ~GameObject();

	
};

