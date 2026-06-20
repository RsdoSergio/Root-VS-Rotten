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
		"audio/TABLERO3.mp3"
	};
	constexpr int N = sizeof(canciones) / sizeof(canciones[0]);

	stopMusica();
	playMusica(canciones[rand() % N], true);
}

void Audio::playMusicaCombate()
{
	static const char* canciones[] = {
		"audio/COMBATE1.mp3",
		"audio/COMBATE2.mp3",
		"audio/COMBATE3.mp3",
		"audio/COMBATE4.mp3",
		"audio/COMBATE5.mp3"
	};
	constexpr int N = sizeof(canciones) / sizeof(canciones[0]);

	stopMusica();
	playMusica(canciones[rand() % N], true);
}