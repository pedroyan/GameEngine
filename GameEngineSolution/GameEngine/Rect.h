#pragma once
#include "Vec2.h"
class Rect {
	public:
		//variaveis

		int X;
		int Y;
		int W;
		int H;

		//Operadores
		Rect operator+(const Vec2 vec);

		//M�todo

		/// <summary>
		/// Calcula as coordenadas do centro do ret�ngulo
		/// </summary>
		/// <returns>o centro do ret�ngulo</returns>
		Vec2 GetCenter();

		/// <summary>
		/// Calcula a dist�ncia entre o centro deste ret�ngulo
		/// e do ret�ngulo de destino passado como par�metro
		/// </summary>
		/// <param name="otherRectangle">ret�ngulo de destino</param>
		/// <returns>a dist�ncia entre os dois ret�ngulos</returns>
		float DistanceFrom(Rect otherRectangle);

		/// <summary>
		/// Verifica se o ponto passado se encontra
		/// dentro do ret�ngulo
		/// </summary>
		/// <param name="coordinates">ponto a ser verificado</param>
		/// <returns>booleano indicando se o ponto se encontra dentro do ret�ngulo</returns>
		bool IsInside(Vec2 coordinates);

		Rect();
		Rect(int x, int y, int w, int h);
		~Rect();
		
};

