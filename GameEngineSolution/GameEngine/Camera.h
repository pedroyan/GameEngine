#pragma once
#include "GameObject.h"
#include "Vec2.h"
class Camera {
	public:
		static void Follow(GameObject* newFocus);
		static void Unfollow();
		static void Update(float dt);
		static bool IsBeeingFollowed(GameObject* followed);
		static Vec2 pos;
		static Vec2 speed;
		static float Zoom;

	private:
		static GameObject* focus;
		static void UpdateOnInput(float dt);
		static void UpdateOnFocus();
};

