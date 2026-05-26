#pragma once
#include "ETSIDI.h"

enum class EstadoMenu {
	OPCION_0,   //jugar
	OPCION_1    //salir
};

class Menu
{
	EstadoMenu opcionSeleccionada = EstadoMenu::OPCION_0;
	bool confirmadoJugar = false;

public:
	void dibuja() const;
	void tecla(unsigned char key);
	bool seEligeJugar() const { return confirmadoJugar; }
};
