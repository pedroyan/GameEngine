#pragma once
class Debug {
	public:
	/// <summary>
	/// Cria um quadrado em volta da posicao inserida
	/// </summary>
	/// <param name="x">posicao x</param>
	/// <param name="y">posicao y</param>
	/// <param name="w">largura w</param>
	/// <param name="h">altura h</param>
	/// <param name="r">numero de 0 a 255 do red</param>
	/// <param name="g">numero de 0 a 255 do green</param>
	/// <param name="b">numero de 0 a 255 do blue</param>
	static void MakeDebugSquare(float x, float y, float w, float h, int r, int g, int b);
	private:
	// Não é possivel instanciar essa classe
};

