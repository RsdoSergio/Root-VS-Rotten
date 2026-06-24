#pragma once
#include "hechizo.h"

class hechizoExchange : public HechizoBase	
{
	Pos origen;

public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "EXCHANGE"; }

	// el jugador elige la primera pieza (debe ser aliada)

	bool elegirOrigen(Tablero& tablero, Pieza* caster, Pos posOrigen);

	bool tieneOrigenElegido() const { return origen.esValida(); }
	void resetear() { origen = Pos(); }
	std::string getMensajeSeleccion() const override { return "Selecciona al aliado que quieres intercambiar"; }
	std::string getMensajeExito() const override { return "Intercambio realizado con exito"; }

};

