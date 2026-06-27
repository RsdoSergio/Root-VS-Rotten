#pragma once
#include "hechizo.h"

class hechizoTeleport : public HechizoBase
{
	Pos origen;

public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "TELEPORT"; }

	// el jugador elige la pieza aliada que se va a teletransportar

	bool elegirOrigen(Tablero& tablero, Pieza* caster, Pos posOrigen);

	bool tieneOrigenElegido() const { return origen.esValida(); }
	void resetear() { origen = Pos(); }
	std::string getMensajeSeleccion() const override { return "Selecciona la casilla destino, vacia"; }
	std::string getMensajeExito() const override { return "El mago ha teletransportado a su aliado"; }
};