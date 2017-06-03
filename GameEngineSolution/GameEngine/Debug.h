#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "SDL.h"

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

	/// <summary>
	/// Cria um quadrado em volta da posicao inserida
	/// </summary>
	/// <param name="x">posicao x</param>
	/// <param name="y">posicao y</param>
	/// <param name="w">largura da caixa</param>
	/// <param name="h">altura da caixa</param>
	/// <param name="color">cor da caixa</param>
	static void MakeDebugSquare(float x, float y, float w, float h, SDL_Color color);

	/// <summary>
	/// Cria um quadrado de debug em volta da posição passada,
	/// traçando duas retas que se interseccionam no meio da
	/// box passada.
	/// </summary>
	/// <param name="positionBox">Box sendo analisada</param>
	/// <param name="boxColor">Cor da caixa desenhada</param>
	static void MakeCenteredDebugSquare(const Rect& positionBox, SDL_Color boxColor);

	private:
	Debug();
};

