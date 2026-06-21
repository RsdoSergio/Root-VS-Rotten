#pragma once
#include "ETSIDI.h"

//menu general (pantalla):
//      0 = principal, 1 = instrucciones, 2 = creditos
//dentro de menu principal (opcion):
//      0 = jugar, 1 = instrucciones, 2 = creditos, 3 = salir

class Menu
{
	int pantalla = 0;
	int opcion = 0;
	bool confirmadoJugar = false;

public:
	void dibuja();
	void tecla(unsigned char key);
	bool seEligeJugar() const { return confirmadoJugar; }
	void dibujaPausa(int opcion) const;
};
