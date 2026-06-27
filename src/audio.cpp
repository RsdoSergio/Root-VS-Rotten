#include "audio.h"
#include <cstdlib>

void Audio::playMusica(const char* nombre, bool repite) {
	ETSIDI::playMusica(nombre, repite);
}
void Audio::stopMusica() {
	ETSIDI::stopMusica();
}
void Audio::playSonido(const char* nombre) {
	ETSIDI::play(nombre);
}

//mezclaz un array (Fisher-Yates)
static void mezclar(int* arr, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
	}
}

void Audio::playMusicaTablero()
{
	static const char* canciones[] = {
		"audio/TABLERO1.mp3",
		"audio/TABLERO2.mp3",
		"audio/TABLERO3.mp3",
		"audio/TABLERO4.mp3",
		"audio/TABLERO5.mp3",
		"audio/TABLERO6.mp3",
		"audio/TABLERO7.mp3"
	};
	constexpr int N = 7;
	static int orden[N] = { 0,1,2,3,4,5,6 };
	static int cursor = N;

	if (cursor >= N) { mezclar(orden, N); cursor = 0; }

	stopMusica();
	playMusica(canciones[orden[cursor++]], true);
}

void Audio::playMusicaCombate()
{
	static const char* canciones[] = {
		"audio/COMBATE1.mp3",
		"audio/COMBATE2.mp3",
		"audio/COMBATE3.mp3",
		"audio/COMBATE4.mp3",
		"audio/COMBATE5.mp3",
		"audio/COMBATE6.mp3",
		"audio/COMBATE7.mp3",
		"audio/COMBATE8.mp3"
	};
	constexpr int N = 8;
	static int orden[N] = { 0,1,2,3,4,5,6,7 };
	static int cursor = N;

	if (cursor >= N) { mezclar(orden, N); cursor = 0; }

	stopMusica();
	playMusica(canciones[orden[cursor++]], true);
}

void Audio::playMusicaViolenta()
{
	static const char* canciones[] = {
		"audio/VIOLENTA1.mp3",
		"audio/VIOLENTA2.mp3",
		"audio/VIOLENTA3.mp3",
		"audio/VIOLENTA4.mp3",
		"audio/VIOLENTA5.mp3",
		"audio/VIOLENTA6.mp3",
		"audio/VIOLENTA7.mp3"
	};
	constexpr int N = 7;
	static int orden[N] = { 0,1,2,3,4,5,6 };
	static int cursor = N;

	if (cursor >= N) { mezclar(orden, N); cursor = 0; }

	stopMusica();
	playMusica(canciones[orden[cursor++]], true);
}

void Audio::playMusicaFinal()
{
	static const char* canciones[] = {
		"audio/PANTALLAFINAL1.mp3",
		"audio/PANTALLAFINAL2.mp3",
		"audio/PANTALLAFINAL3.mp3",
		"audio/PANTALLAFINAL4.mp3"
	};
	constexpr int N = 4;
	static int orden[N] = { 0,1,2,3 };
	static int cursor = N;

	if (cursor >= N) { mezclar(orden, N); cursor = 0; }

	stopMusica();
	playMusica(canciones[orden[cursor++]], false);
}