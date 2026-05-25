#pragma once
#include "ETSIDI.h"

class Audio {
public:
	static void playMusica(const char* nombre, bool repite = true);
	static void stopMusica();
	static void playSonido(const char* nombre);
};