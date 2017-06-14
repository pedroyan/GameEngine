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

		//Método

		/// <summary>
		/// Calcula as coordenadas do centro do retângulo
		/// </summary>
		/// <returns>o centro do retângulo</returns>
		Vec2 GetCenter();

		/// <summary>
		/// Calcula a distância entre o centro deste retângulo
		/// e do retângulo de destino passado como parâmetro
		/// </summary>
		/// <param name="otherRectangle">retângulo de destino</param>
		/// <returns>a distância entre os dois retângulos</returns>
		float DistanceFrom(Rect otherRectangle);

		/// <summary>
		/// Verifica se o ponto passado se encontra
		/// dentro do retângulo
		/// </summary>
		/// <param name="coordinates">ponto a ser verificado</param>
		/// <returns>booleano indicando se o ponto se encontra dentro do retângulo</returns>
		bool IsInside(Vec2 coordinates);

		/// <summary>
		/// Verifica se o ponto passado se encontra
		/// dentro do retângulo
		/// </summary>
		/// <param name="coordinates">coordenada x</param>
		/// <param name="coordinates">coordenada y</param>
		/// <returns>booleano indicando se o ponto se encontra dentro do retângulo</returns>
		bool IsInside(float x, float y);

		/// <summary>
		/// Pega a posição do player no mundo, considerando os parametros de camera
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

