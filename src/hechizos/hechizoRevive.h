#pragma once
#include "hechizo.h"
#include <vector>

class hechizoRevive : public HechizoBase
{
	Pieza* piezaElegida = nullptr;

public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "REVIVE"; }

	std::vector<Pieza*>& getCandidatas(Tablero& tablero, Pieza* caster) const;

	bool elegirPieza(Tablero& tablero, Pieza* caster, int indice);

	bool tienePiezaElegida() const { return piezaElegida != nullptr; }
	void resetear() { piezaElegida = nullptr; }
	std::string getMensajeSeleccion() const override { return "Selecciona la casilla junto al mago"; }
	std::string getMensajeExito() const override { return "El mago ha revivido a su aliado"; }
};