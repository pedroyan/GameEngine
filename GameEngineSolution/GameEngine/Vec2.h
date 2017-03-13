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
		/// Calcula a distancia entre dois pontos
		/// </summary>
		/// <param name="otherPoint">Ponto que se deseja calcular a distancia a partir do ponto atual</param>
		/// <returns></returns>
		float GetDistance(Vec2 otherPoint);

		/// <summary>
		/// Calcula o ângulo do vetor distância entre dois pontos, considerando
		/// a instancia atual como o ponto de partida e a instancia passada como
		/// o ponto de destino
		/// </summary>
		/// <param name="destinyPoint">ponto de destino</param>
		/// <returns></returns>
		float GetDistanceVectorAngle(Vec2 destinyPoint);

		/// <summary>
		/// Calcula o ângulo, em radianos, do vetor em relação ao eixo X.
		/// </summary>
		/// <returns>o ângulo em radianos</returns>
		float GetXAxisAngle();

		/// <summary>
		/// Rotaciona o vetor num determinado ângulo. Lembrando que,
		/// como o eixo Y cresce para baixo, passar um angulo positivo
		/// irá rotacionar o vetor no sentido horário.
		/// </summary>
		/// <param name="angulo">Angulo em radianos da rotação</param>
		void Rotate(float angulo);

		/// <summary>
		/// Inicializa um vetor 2D com os parametros passados
		/// </summary>
		/// <param name="x">Componente x do vetor</param>
		/// <param name="y">Componente Y do vetor</param>
		Vec2(float x, float y);

		~Vec2();
};

