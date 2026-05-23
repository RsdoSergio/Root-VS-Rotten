#include "audio.h"

void Audio::playMusica(const char* nombre, bool repite) {
	ETSIDI::playMusica(nombre, repite);
}

void Audio::stopMusica() {
	ETSIDI::stopMusica();
}

void Audio::playSonido(const char* nombre) {
	ETSIDI::play(nombre);
}