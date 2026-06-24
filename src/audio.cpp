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

void Audio::playMusicaTablero()
{
	static const char* canciones[] = {
		"audio/TABLERO1.mp3",
		"audio/TABLERO2.mp3",
		"audio/TABLERO3.mp3",
		"audio/TABLERO4.mp3",
		"audio/TABLERO5.mp3",
		"audio/TABLERO6.mp3",
		"audio/TABLERO7.mp3",
	};
	constexpr int N = sizeof(canciones) / sizeof(canciones[0]);
	static int ultimaCancion = -1;

	int nueva;
	do {
		nueva = rand() % N;
	} while (nueva == ultimaCancion && N > 1);

	ultimaCancion = nueva;
	stopMusica();
	playMusica(canciones[nueva], true);
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
	constexpr int N = sizeof(canciones) / sizeof(canciones[0]);
	static int ultimaCancion = -1;

	int nueva;
	do {
		nueva = rand() % N;
	} while (nueva == ultimaCancion && N > 1);

	ultimaCancion = nueva;
	stopMusica();
	playMusica(canciones[nueva], true);
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
	constexpr int N = sizeof(canciones) / sizeof(canciones[0]);
	static int ultimaCancion = -1;

	int nueva;
	do {
		nueva = rand() % N;
	} while (nueva == ultimaCancion && N > 1);

	ultimaCancion = nueva;
	stopMusica();
	playMusica(canciones[nueva], true);
}