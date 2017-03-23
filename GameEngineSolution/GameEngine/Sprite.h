#pragma once
#include<string>
#include <SDL_image.h>

using std::string;

class Sprite {
	public:
		Sprite();
		Sprite(string file);

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
		void Render(int x, int y, float angle = 0);
		int GetWidth();
		int GetHeight();
		bool IsOpen();

		void SetScaleX(float scale);
		void SetScaleY(float scale);

	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
		float scaleX;
		float scaleY;
};

