#pragma once
class Vec2 {
	public:
		//Variaveis

		float X;
		float Y;

		//Operadores

		Vec2 operator+(const Vec2 soma);
		Vec2 operator-(const Vec2 subtracao);
		Vec2 operator*(const float escalar);
		Vec2 operator/(const float escalar);

		//Métodos

		Vec2();

		/// <summary>
		/// Calcula a magnitude(tamanho) de um vetor
		/// </summary>
		/// <returns>A magnitude do vetor </returns>
		float Magnitude();
		
		/// <summary>
		/// Calcula o vetor normalizado
		/// </summary>
		/// <returns>o vetor normalizado</returns>
		Vec2 Normalize();

		/// <summary>
		/// Calcula a distancia entre o vetor atual e o vetor passado
		/// </summary>
		/// <param name="otherPoint">Ponto que se deseja calcular a distancia a partir do ponto atual</param>
		/// <returns></returns>
		float GetDistance(Vec2 otherPoint);

		/// <summary>
		/// Inicializa um vetor 2D com os parametros passados
		/// </summary>
		/// <param name="x">Componente x do vetor</param>
		/// <param name="y">Componente Y do vetor</param>
		Vec2(float x, float y);

		~Vec2();
};

