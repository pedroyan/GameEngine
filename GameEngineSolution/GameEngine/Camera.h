#pragma once
#include "GameObject.h"
#include "Vec2.h"
class Camera {
	public:
		static void Follow(GameObject* newFocus);
		static void Unfollow();
		static void Update(float dt);
		static bool IsBeeingFollowed(GameObject* followed);

		/// <summary>
		/// Seta o zoom linearmente para um valor passado
		/// </summary>
		/// <param name="zoom">Valor final do zoom</param>
		/// <param name="time">Tempo, em segundos, decorrido para que o zoom vá do seu valor atual para o valor passado</param>
		static void ZoomTo(float zoom, float time);

		static Vec2 pos;
		static Vec2 speed;
		static float Zoom;

	private:
		static GameObject* focus;
		static float targetZoom;
		static float zoomPerSec;
		static void UpdateOnInput(float dt);
		static void UpdateOnFocus();
		static void UpdateZoom(float dt);
};

