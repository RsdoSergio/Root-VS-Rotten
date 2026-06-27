#pragma once
#include "ETSIDI.h"

class Menu
{
	int pantalla = 0;
	int opcion = 0;
	bool confirmadoJugar = false;

public:
	void dibuja();
	void tecla(unsigned char key);
	bool seEligeJugar() const { return confirmadoJugar; }
	void reinicia() { confirmadoJugar = false; }
	void dibujaPausa(int opcion) const;
	void dibujaControlesPausa() const;
	void dibujaPuntuaciones() const;
};
