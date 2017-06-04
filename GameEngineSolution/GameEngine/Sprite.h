#pragma once
#include<string>
#include <SDL_image.h>
#include "Vec2.h"
#include <memory>

using std::string;
using std::shared_ptr;

class Sprite {
	public:
		Sprite();
		Sprite(string file, int frameCount = 1, float frameTime = 1);

		~Sprite();

		void Open(string file);

		/// <summary>
		/// Seta o retângulo de clipping (recorte) da textura
		/// </summary>
		/// <param name="x">coordenada x</param>
		/// <param name="y">coordenada y</param>
		/// <param name="w">Largura do retângulo</param>
		/// <param name="h">Altura do retângulo</param>
		void SetClip(int x, int y, int w, int h);

		/// <summary>
		/// Realiza a renderização do sprite
		/// </summary>
		/// <param name="x">Posicao x</param>
		/// <param name="y">Posicao Y</param>
		/// <param name="angle">Angulo, em radianos, que o sprite será girado no sentido horario</param>
		void Render(int x, int y, float angle = 0, bool flip=false, float Zoom =1);
		void Render(Vec2 pos, float angle = 0, bool flip = false, float Zoom=1);
		int GetWidth();
		int GetHeight();
		bool IsOpen();
		void Update(float dt);
		void SetFrame(int frame);
		void SetFrameCount(int frameCount);
		void SetFrameTime(float frameTime);

		/// <summary>
		/// Retorna as coordenadas x, y de onde o canto superior esquerdo do sprite
		/// precisa ser renderizado para que o sprite fique centralizado na posicao
		/// passada
		/// </summary>
		/// <param name="center">Ponto onde o sprite deve ser centralizado</param>
		/// <returns>Coordenadas de renderização do sprite</returns>
		Vec2 GetCentralizedRenderPoint(Vec2 center);

		void SetScaleX(float scale);
		void SetScaleY(float scale);

	private:
		shared_ptr<SDL_Texture> texture;
		int width;
		int height;
		SDL_Rect clipRect;
		float scaleX;
		float scaleY;

		int frameCount;
		int currentFrame;
		float timeElapsed;
		float frameTime;

		/// <summary>
		/// Largura de cada frame
		/// </summary>
		int frameWidth;
};

