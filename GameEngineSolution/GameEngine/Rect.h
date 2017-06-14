#pragma once
#include "Vec2.h"
class Rect {
	public:
		//variaveis

		float X;
		float Y;
		float W;
		float H;

		//Operadores
		Rect operator+(const Vec2 vec);
		Rect& operator+=(const Vec2 vec);

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

		/// <summary>
		/// Verifica se o ponto passado se encontra
		/// dentro do ret�ngulo
		/// </summary>
		/// <param name="coordinates">coordenada x</param>
		/// <param name="coordinates">coordenada y</param>
		/// <returns>booleano indicando se o ponto se encontra dentro do ret�ngulo</returns>
		bool IsInside(float x, float y);

		/// <summary>
		/// Pega a posi��o do player no mundo, considerando os parametros de camera
		/// </summary>
		/// <param name="withZoom">Flag booleana indicando se o zoom da camera deve ser considerado</param>
		/// <returns>Posicao do canto superior esquerdo do player</returns>
		Vec2 GetWorldRenderPosition(bool withZoom=false) const;

		/// <summary>
		/// Pega a box do player no mundo, considerando TODOS os parametros de camera
		/// </summary>
		/// <returns>A box do player no mundo</returns>
		Rect GetWorldRenderBox() const;

		void SetCenter(float x, float y);
		void SetCenter(Vec2 vector);

		Rect();
		Rect(float x, float y, float w, float h);
		~Rect();
		
};

